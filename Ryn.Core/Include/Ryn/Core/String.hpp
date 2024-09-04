#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Span.hpp>

namespace Ryn::Core
{
    class String
    {
      private:
        usz _length{};
        char* _data{};

      public:
        consteval String() {};

        constexpr String(char* str, usz length) :
            _length(length),
            _data(str) {}

        template <usz N>
        constexpr String(const char (&str)[N]) :
            _length(N - 1)
        {
            Construct(str, N - 1);
        }

        explicit String(Span<const char> span) { Construct(&span[0], span.Length()); }

        String(const String& other);
        String(String&& other);
        ~String();

        String& operator=(const String& other);
        String& operator=(String&& other);

      private:
        void Construct(const char* data, usz length);

      public:
        constexpr usz Length() const { return _length; }

        constexpr char& operator[](usz index) { return _data[index]; }
        constexpr const char& operator[](usz index) const { return _data[index]; }

        String& Append(const char c) { return Append(&c, 1); }
        String& Append(const char* str) { return Append(&str[0], String::Length(str)); }
        String& Append(const String& other) { return Append(&other[0], other.Length()); }
        String& Append(Span<const char> span) { return Append(&span[0], span.Length()); }
        String& Append(i8 value) { return Append(static_cast<i64>(value)); }
        String& Append(i16 value) { return Append(static_cast<i64>(value)); }
        String& Append(i32 value) { return Append(static_cast<i64>(value)); }
        String& Append(i64 value) { char buffer[20]; return Append(String::Format(Span<char>(buffer, sizeof(buffer)), value)); }
        String& Append(isz value) { return Append(static_cast<i64>(value)); }
        String& Append(u8 value) { return Append(static_cast<u64>(value)); }
        String& Append(u16 value) { return Append(static_cast<u64>(value)); }
        String& Append(u32 value) { return Append(static_cast<u64>(value)); }
        String& Append(u64 value) { char buffer[20]; return Append(String::Format(Span<char>(buffer, sizeof(buffer)), value)); }
        String& Append(usz value) { return Append(static_cast<u64>(value)); }
        String& Append(f32 value) { return Append(static_cast<f64>(value)); }
        String& Append(f64 value) { char buffer[32]; return Append(String::Format(Span<char>(buffer, sizeof(buffer)), value)); }

      private:
        String& Append(const char* data, usz length);

      public:
        String& operator+=(const char c) { return Append(c); }
        String& operator+=(const char* str) { return Append(str); }
        String& operator+=(const String& other) { return Append(other); }
        String& operator+=(Span<const char> span) { return Append(span); }
        String& operator+=(i8 value) { return Append(value); }
        String& operator+=(i16 value) { return Append(value); }
        String& operator+=(i32 value) { return Append(value); }
        String& operator+=(i64 value) { return Append(value); }
        String& operator+=(isz value) { return Append(value); }
        String& operator+=(u8 value) { return Append(value); }
        String& operator+=(u16 value) { return Append(value); }
        String& operator+=(u32 value) { return Append(value); }
        String& operator+=(u64 value) { return Append(value); }
        String& operator+=(usz value) { return Append(value); }
        String& operator+=(f32 value) { return Append(value); }
        String& operator+=(f64 value) { return Append(value); }

        String operator+(const char c) const { return String{*this}.Append(c); }
        String operator+(const char* str) const { return String{*this}.Append(str); }
        String operator+(const String& other) const { return String{*this}.Append(other); }
        String operator+(Span<const char> span) const { return String{*this}.Append(span); }
        String operator+(i8 value) const { return String{*this}.Append(value); }
        String operator+(i16 value) const { return String{*this}.Append(value); }
        String operator+(i32 value) const { return String{*this}.Append(value); }
        String operator+(i64 value) const { return String{*this}.Append(value); }
        String operator+(isz value) const { return String{*this}.Append(value); }
        String operator+(u8 value) const { return String{*this}.Append(value); }
        String operator+(u16 value) const { return String{*this}.Append(value); }
        String operator+(u32 value) const { return String{*this}.Append(value); }
        String operator+(u64 value) const { return String{*this}.Append(value); }
        String operator+(usz value) const { return String{*this}.Append(value); }
        String operator+(f32 value) const { return String{*this}.Append(value); }
        String operator+(f64 value) const { return String{*this}.Append(value); }

        String& Insert(usz to, const char c) { return Insert(to, &c, 1); }
        String& Insert(usz to, const char* str) { return Insert(to, &str[0], String::Length(str)); }
        String& Insert(usz to, const String& other) { return Insert(to, &other[0], other.Length()); }
        String& Insert(usz to, Span<const char> span) { return Insert(to, &span[0], span.Length()); }
        String& Insert(usz to, i8 value) { return Insert(to, static_cast<i64>(value)); }
        String& Insert(usz to, i16 value) { return Insert(to, static_cast<i64>(value)); }
        String& Insert(usz to, i32 value) { return Insert(to, static_cast<i64>(value)); }
        String& Insert(usz to, i64 value) { char buffer[20]; return Insert(to, String::Format(Span<char>(buffer, 20), value)); }
        String& Insert(usz to, isz value) { return Insert(to, static_cast<i64>(value)); }
        String& Insert(usz to, u8 value) { return Insert(to, static_cast<u64>(value)); }
        String& Insert(usz to, u16 value) { return Insert(to, static_cast<u64>(value)); }
        String& Insert(usz to, u32 value) { return Insert(to, static_cast<u64>(value)); }
        String& Insert(usz to, u64 value) { char buffer[20]; return Insert(to, String::Format(Span<char>(buffer, 20), value)); }
        String& Insert(usz to, usz value) { return Insert(to, static_cast<u64>(value)); }
        String& Insert(usz to, f32 value) { return Insert(to, static_cast<f64>(value)); }
        String& Insert(usz to, f64 value) { char buffer[32]; return Insert(to, String::Format(Span<char>(buffer, 32), value)); }

      private:
        String& Insert(usz to, const char* data, usz length);

      public:
        String& Remove(usz at) { return Remove(at, at); }
        String& Remove(usz from, usz to);

        constexpr bool operator==(const String& other) const { return _length == other._length && Memory::Compare(_data, other._data, _length) == 0; }
        constexpr bool operator!=(const String& other) const { return !(*this == other); }

      public:
        constexpr Span<char> ToSpan() const { return Span<char>(_data, _length); }
        constexpr Span<char> ToSpan(usz start) const { return ToSpan().Slice(start); }
        constexpr Span<char> ToSpan(usz start, usz length) const { return ToSpan().Slice(start, length); }

        constexpr operator Span<char>() const { return ToSpan(); }
        constexpr operator Span<const char>() const { return ToSpan(); }

      public:
        static usz Length(const char* str);

        static Span<const char> Format(Span<char> buffer, i64 value);
        static Span<const char> Format(Span<char> buffer, u64 value);
        static Span<const char> Format(Span<char> buffer, f64 value, u64 precision = 1e4);
    };
}
