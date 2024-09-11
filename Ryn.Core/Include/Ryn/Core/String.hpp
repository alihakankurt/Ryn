#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Memory.hpp>
#include <Ryn/Core/Iterator.hpp>
#include <Ryn/Core/Span.hpp>

namespace Ryn
{
    class String
    {
      private:
        char* _data;
        u32 _length;

      public:
        constexpr String() :
            _data{},
            _length{} {}

        constexpr String(char* data, u32 length) :
            _data{data},
            _length{length} {}

        template <u32 N>
        constexpr String(const char (&str)[N]) { Construct(&str[0], N - 1); }
        explicit String(Span<const char> span) { Construct(&span[0], span.Length()); }

        String(const String& other);
        String(String&& other);
        ~String();

        String& operator=(const String& other);
        String& operator=(String&& other);

      private:
        void Construct(const char* data, u32 length);

      public:
        constexpr u32 Length() const { return _length; }

        constexpr char& operator[](u32 index) { return _data[index]; }
        constexpr const char& operator[](u32 index) const { return _data[index]; }

        String& Append(const char c) { return Append(&c, 1); }
        String& Append(const char* str) { return Append(&str[0], String::Length(str)); }
        String& Append(const String& other) { return Append(&other[0], other.Length()); }
        String& Append(Span<const char> span) { return Append(&span[0], span.Length()); }

        String& Append(bool value)
        {
            char buffer[String::MaxBoolLength];
            return Append(String::Format(buffer, value));
        }

        String& Append(i8 value) { return Append(static_cast<i64>(value)); }
        String& Append(i16 value) { return Append(static_cast<i64>(value)); }
        String& Append(i32 value) { return Append(static_cast<i64>(value)); }
        String& Append(i64 value)
        {
            char buffer[String::MaxIntLength];
            return Append(String::Format(buffer, value));
        }

        String& Append(u8 value) { return Append(static_cast<u64>(value)); }
        String& Append(u16 value) { return Append(static_cast<u64>(value)); }
        String& Append(u32 value) { return Append(static_cast<u64>(value)); }
        String& Append(u64 value)
        {
            char buffer[String::MaxIntLength];
            return Append(String::Format(buffer, value));
        }

        String& Append(f32 value) { return Append(static_cast<f64>(value)); }
        String& Append(f64 value)
        {
            char buffer[String::MaxFloatLength];
            return Append(String::Format(buffer, value));
        }

      private:
        String& Append(const char* data, u32 length);

      public:
        String& operator+=(const char c) { return Append(c); }
        String& operator+=(const char* str) { return Append(str); }
        String& operator+=(const String& other) { return Append(other); }
        String& operator+=(Span<const char> span) { return Append(span); }

        String& operator+=(bool value) { return Append(value); }

        String& operator+=(i8 value) { return Append(value); }
        String& operator+=(i16 value) { return Append(value); }
        String& operator+=(i32 value) { return Append(value); }
        String& operator+=(i64 value) { return Append(value); }

        String& operator+=(u8 value) { return Append(value); }
        String& operator+=(u16 value) { return Append(value); }
        String& operator+=(u32 value) { return Append(value); }
        String& operator+=(u64 value) { return Append(value); }

        String& operator+=(f32 value) { return Append(value); }
        String& operator+=(f64 value) { return Append(value); }

        String operator+(const char c) const { return String{*this}.Append(c); }
        String operator+(const char* str) const { return String{*this}.Append(str); }
        String operator+(const String& other) const { return String{*this}.Append(other); }
        String operator+(Span<const char> span) const { return String{*this}.Append(span); }

        String operator+(bool value) const { return String{*this}.Append(value); }

        String operator+(i8 value) const { return String{*this}.Append(value); }
        String operator+(i16 value) const { return String{*this}.Append(value); }
        String operator+(i32 value) const { return String{*this}.Append(value); }
        String operator+(i64 value) const { return String{*this}.Append(value); }

        String operator+(u8 value) const { return String{*this}.Append(value); }
        String operator+(u16 value) const { return String{*this}.Append(value); }
        String operator+(u32 value) const { return String{*this}.Append(value); }
        String operator+(u64 value) const { return String{*this}.Append(value); }

        String operator+(f32 value) const { return String{*this}.Append(value); }
        String operator+(f64 value) const { return String{*this}.Append(value); }

        String& Insert(u32 to, const char c) { return Insert(to, &c, 1); }
        String& Insert(u32 to, const char* str) { return Insert(to, &str[0], String::Length(str)); }
        String& Insert(u32 to, const String& other) { return Insert(to, &other[0], other.Length()); }
        String& Insert(u32 to, Span<const char> span) { return Insert(to, &span[0], span.Length()); }

        String& Insert(u32 to, bool value)
        {
            char buffer[String::MaxBoolLength];
            return Insert(to, String::Format(buffer, value));
        }

        String& Insert(u32 to, i8 value) { return Insert(to, static_cast<i64>(value)); }
        String& Insert(u32 to, i16 value) { return Insert(to, static_cast<i64>(value)); }
        String& Insert(u32 to, i32 value) { return Insert(to, static_cast<i64>(value)); }
        String& Insert(u32 to, i64 value)
        {
            char buffer[String::MaxIntLength];
            return Insert(to, String::Format(buffer, value));
        }

        String& Insert(u32 to, u8 value) { return Insert(to, static_cast<u64>(value)); }
        String& Insert(u32 to, u16 value) { return Insert(to, static_cast<u64>(value)); }
        String& Insert(u32 to, u32 value) { return Insert(to, static_cast<u64>(value)); }
        String& Insert(u32 to, u64 value)
        {
            char buffer[String::MaxIntLength];
            return Insert(to, String::Format(buffer, value));
        }

        String& Insert(u32 to, f32 value) { return Insert(to, static_cast<f64>(value)); }
        String& Insert(u32 to, f64 value)
        {
            char buffer[String::MaxFloatLength];
            return Insert(to, String::Format(buffer, value));
        }

      private:
        String& Insert(u32 to, const char* data, u32 length);

      public:
        String& Remove(u32 at) { return Remove(at, at); }
        String& Remove(u32 from, u32 to);

        constexpr bool operator==(const String& other) const { return _length == other._length && Memory::Compare(_data, other._data, _length) == 0; }
        constexpr bool operator!=(const String& other) const { return !(*this == other); }

      public:
        constexpr Span<char> ToSpan() const { return Span<char>{_data, _length}; }
        constexpr Span<char> ToSpan(u32 start) const { return ToSpan().Slice(start); }
        constexpr Span<char> ToSpan(u32 start, u32 length) const { return ToSpan().Slice(start, length); }

        constexpr operator Span<char>() const { return ToSpan(); }
        constexpr operator Span<const char>() const { return ToSpan(); }

      public:
        constexpr Iterator<char> begin() { return Iterator<char>{_data}; }
        constexpr Iterator<const char> begin() const { return Iterator<const char>{_data}; }
        constexpr Iterator<char> end() { return Iterator<char>{_data + _length}; }
        constexpr Iterator<const char> end() const { return Iterator<const char>{_data + _length}; }

      public:
        static u32 Length(const char* str);

        static constexpr u32 MaxBoolLength = 5;
        static constexpr u32 MaxIntLength = 20;
        static constexpr u32 MaxFloatLength = 27;

        static Span<char> Format(Span<char> span, bool value);
        static Span<char> Format(Span<char> span, i64 value);
        static Span<char> Format(Span<char> span, u64 value);
        static Span<char> Format(Span<char> span, f64 value);
    };
}
