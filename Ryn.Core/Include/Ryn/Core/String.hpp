#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Memory.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Iterable.hpp>
#include <Ryn/Core/Span.hpp>

namespace Ryn
{
    class String : public Iterable<char, LinearIterator<char>, LinearIterator<const char>>
    {
      private:
        char* _data;
        usz _length;

      public:
        constexpr String() :
            _data{},
            _length{} {}

        constexpr String(char* data, usz length) :
            _data{data},
            _length{length} {}

        template <usz N>
        String(const char (&str)[N])
        {
            Create(&str[0], N - 1);
        }

        explicit String(Span<const char> span)
        {
            Create(span.Data(), span.Length());
        }

        String(const String& other)
        {
            Create(other._data, other._length);
        }

        String(String&& other) :
            _data{Utility::Exchange(other._data)},
            _length{Utility::Exchange(other._length)} {}

        ~String()
        {
            Destroy();
        }

        String& operator=(const String& other)
        {
            if (this != &other)
            {
                Destroy();
                Create(other._data, other._length);
            }
            return *this;
        }

        String& operator=(String&& other)
        {
            if (this != &other)
            {
                Destroy();
                _data = Utility::Exchange(other._data);
                _length = Utility::Exchange(other._length);
            }
            return *this;
        }

      private:
        void Create(const char* data, usz length);
        void Destroy();

      public:
        constexpr usz Length() const { return _length; }

        String& Append(const char c) { return Append(&c, 1); }
        String& Append(const char* str) { return Append(&str[0], String::Length(str)); }
        String& Append(const String& other) { return Append(other.Data(), other.Length()); }
        String& Append(Span<const char> span) { return Append(span.Data(), span.Length()); }

        String& Append(bool value)
        {
            char buffer[String::MaxBoolLength];
            Span<char> span = String::Format(buffer, value);
            return Append(span.Data(), span.Length());
        }

        template <Traits::Integer TValue>
        String& Append(TValue value)
        {
            char buffer[String::MaxIntLength];
            Span<char> span;
            if constexpr (Traits::SignedInteger<TValue>)
                span = String::Format(buffer, static_cast<i64>(value));
            else
                span = String::Format(buffer, static_cast<u64>(value));
            return Append(span.Data(), span.Length());
        }

        template <Traits::FloatingPoint TValue>
        String& Append(TValue value)
        {
            char buffer[String::MaxFloatLength];
            Span<char> span = String::Format(buffer, static_cast<f64>(value));
            return Append(span.Data(), span.Length());
        }

      private:
        String& Append(const char* data, usz length);

      public:
        String& operator+=(const char c) { return Append(c); }
        String& operator+=(const char* str) { return Append(str); }
        String& operator+=(const String& other) { return Append(other); }
        String& operator+=(Span<const char> span) { return Append(span); }

        String& operator+=(bool value) { return Append(value); }

        template <Traits::Number TValue>
        String& operator+=(TValue value)
        {
            return Append(value);
        }

        String operator+(const char c) const { return String{*this}.Append(c); }
        String operator+(const char* str) const { return String{*this}.Append(str); }
        String operator+(const String& other) const { return String{*this}.Append(other); }
        String operator+(Span<const char> span) const { return String{*this}.Append(span); }

        String operator+(bool value) const { return String{*this}.Append(value); }

        template <Traits::Number TValue>
        String operator+(TValue value) const
        {
            return String{*this}.Append(value);
        }

        String& Insert(usz to, const char c) { return Insert(to, &c, 1); }
        String& Insert(usz to, const char* str) { return Insert(to, &str[0], String::Length(str)); }
        String& Insert(usz to, const String& other) { return Insert(to, other.Data(), other.Length()); }
        String& Insert(usz to, Span<const char> span) { return Insert(to, span.Data(), span.Length()); }

        String& Insert(usz to, bool value)
        {
            char buffer[String::MaxBoolLength];
            Span<char> span = String::Format(buffer, value);
            return Insert(to, span.Data(), span.Length());
        }

        template <Traits::Integer TValue>
        String& Insert(usz to, TValue value)
        {
            char buffer[String::MaxIntLength];
            Span<char> span;
            if constexpr (Traits::SignedInteger<TValue>)
                span = String::Format(buffer, static_cast<i64>(value));
            else
                span = String::Format(buffer, static_cast<u64>(value));
            return Insert(to, span.Data(), span.Length());
        }

        template <Traits::FloatingPoint TValue>
        String& Insert(usz to, TValue value)
        {
            char buffer[String::MaxFloatLength];
            Span<char> span = String::Format(buffer, static_cast<f64>(value));
            return Insert(to, span.Data(), span.Length());
        }

      private:
        String& Insert(usz to, const char* data, usz length);

      public:
        String& Remove(usz at) { return Remove(at, at); }
        String& Remove(usz from, usz to);

        constexpr bool operator==(const String& other) const { return _length == other._length && Memory::Compare(_data, other._data, _length) == 0; }
        constexpr bool operator!=(const String& other) const { return !(*this == other); }

      public:
        constexpr Span<char> ToSpan() const { return Span<char>{_data, _length}; }
        constexpr Span<char> ToSpan(usz start) const { return ToSpan().Slice(start); }
        constexpr Span<char> ToSpan(usz start, usz length) const { return ToSpan().Slice(start, length); }

        constexpr operator Span<char>() const { return ToSpan(); }
        constexpr operator Span<const char>() const { return ToSpan(); }

      public:
        constexpr LinearIterator<char> begin() override { return LinearIterator<char>{_data}; }
        constexpr LinearIterator<const char> begin() const override { return LinearIterator<const char>{_data}; }
        constexpr LinearIterator<char> end() override { return LinearIterator<char>{_data + _length}; }
        constexpr LinearIterator<const char> end() const override { return LinearIterator<const char>{_data + _length}; }

      public:
        static usz Length(const char* str);

        static constexpr usz MaxBoolLength = 5;
        static constexpr usz MaxIntLength = 20;
        static constexpr usz MaxFloatLength = 27;

        static Span<char> Format(Span<char> span, bool value);
        static Span<char> Format(Span<char> span, i64 value);
        static Span<char> Format(Span<char> span, u64 value);
        static Span<char> Format(Span<char> span, f64 value);
    };
}
