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
      public:
        using IteratorType = LinearIterator<char>;
        using ConstIteratorType = LinearIterator<const char>;

      private:
        usz _length;
        char* _data;

      public:
        constexpr String() :
            _length{},
            _data{} {}

        constexpr String(usz length, char* data) :
            _length{length},
            _data{data} {}

        template <usz N>
        String(const char (&str)[N])
        {
            Create(N - 1, str);
        }

        explicit String(Span<const char> span)
        {
            Create(span.Length(), span.Data());
        }

        String(const String& other)
        {
            Create(other._length, other._data);
        }

        String(String&& other) :
            _length{Utility::Exchange(other._length)},
            _data{Utility::Exchange(other._data)} {}

        ~String()
        {
            Destroy();
        }

        String& operator=(const String& other)
        {
            if (this != &other)
            {
                Destroy();
                Create(other._length, other._data);
            }
            return *this;
        }

        String& operator=(String&& other)
        {
            if (this != &other)
            {
                Destroy();
                _length = Utility::Exchange(other._length);
                _data = Utility::Exchange(other._data);
            }
            return *this;
        }

      private:
        void Create(usz length, const char* data);
        void Destroy();

      public:
        constexpr usz Length() const { return _length; }

        String& Append(const char c) { return Append(1, &c); }
        String& Append(const char* str) { return Append(String::Length(str), str); }
        String& Append(const String& other) { return Append(other.Length(), other.Data()); }
        String& Append(Span<const char> span) { return Append(span.Length(), span.Data()); }

        String& Append(bool value)
        {
            char buffer[String::MaxBoolLength];
            Span<char> span = String::Format(buffer, value);
            return Append(span.Length(), span.Data());
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
            return Append(span.Length(), span.Data());
        }

        template <Traits::FloatingPoint TValue>
        String& Append(TValue value)
        {
            char buffer[String::MaxFloatLength];
            Span<char> span = String::Format(buffer, static_cast<f64>(value));
            return Append(span.Length(), span.Data());
        }

      private:
        String& Append(usz length, const char* data);

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

        String& Insert(usz to, const char c) { return Insert(to, 1, &c); }
        String& Insert(usz to, const char* str) { return Insert(to, String::Length(str), str); }
        String& Insert(usz to, const String& other) { return Insert(to, other.Length(), other.Data()); }
        String& Insert(usz to, Span<const char> span) { return Insert(to, span.Length(), span.Data()); }

        String& Insert(usz to, bool value)
        {
            char buffer[String::MaxBoolLength];
            Span<char> span = String::Format(buffer, value);
            return Insert(to, span.Length(), span.Data());
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
            return Insert(to, span.Length(), span.Data());
        }

        template <Traits::FloatingPoint TValue>
        String& Insert(usz to, TValue value)
        {
            char buffer[String::MaxFloatLength];
            Span<char> span = String::Format(buffer, static_cast<f64>(value));
            return Insert(to, span.Length(), span.Data());
        }

      private:
        String& Insert(usz to, usz length, const char* data);

      public:
        String& Remove(usz at) { return Remove(at, at); }
        String& Remove(usz from, usz to);

        constexpr bool operator==(const String& other) const { return _length == other._length && Memory::Compare(_data, other._data, _length) == 0; }
        constexpr bool operator!=(const String& other) const { return !(*this == other); }

      public:
        constexpr Span<char> ToSpan() const { return Span<char>{_length, _data}; }
        constexpr Span<char> ToSpan(usz start) const { return ToSpan().Slice(start); }
        constexpr Span<char> ToSpan(usz start, usz length) const { return ToSpan().Slice(start, length); }

        constexpr operator Span<char>() const { return ToSpan(); }
        constexpr operator Span<const char>() const { return ToSpan(); }

      public:
        constexpr IteratorType begin() override { return IteratorType{_data}; }
        constexpr ConstIteratorType begin() const override { return ConstIteratorType{_data}; }
        constexpr IteratorType end() override { return IteratorType{_data + _length}; }
        constexpr ConstIteratorType end() const override { return ConstIteratorType{_data + _length}; }

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
