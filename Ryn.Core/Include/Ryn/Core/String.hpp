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

        String(const Span<char>& span);
        String(const String& other);
        String(String&& other) noexcept;
        ~String();

        String& operator=(const String& other);
        String& operator=(String&& other) noexcept;

      private:
        void Construct(const char* data, usz length);

      public:
        constexpr usz Length() const { return _length; }
        constexpr const char* Raw() const { return _data; }

        constexpr const char& operator[](usz index) const { return _data[index]; }
        constexpr char& operator[](usz index) { return _data[index]; }

        void Append(const char c);
        void Append(const char* str);
        void Append(const String& other);

      private:
        void Append(const char* data, usz length);

      public:
        String& operator+=(const char c);
        String& operator+=(const char* str);
        String& operator+=(const String& other);

        String operator+(const char c) const;
        String operator+(const char* str) const;
        String operator+(const String& other) const;

        void Insert(usz to, const char c);
        void Insert(usz to, const char* str);
        void Insert(usz to, const String& other);

      private:
        void Insert(usz to, const char* data, usz length);

      public:
        void Remove(usz at);
        void Remove(usz from, usz to);

        bool operator==(const String& other) const;
        bool operator!=(const String& other) const;
        bool operator<(const String& other) const;
        bool operator>(const String& other) const;
        bool operator<=(const String& other) const;
        bool operator>=(const String& other) const;

      public:
        Span<char> ToSpan() const;
        Span<char> ToSpan(usz start) const;
        Span<char> ToSpan(usz start, usz length) const;

        constexpr operator Span<char>() const { return ToSpan(); }
        constexpr operator Span<const char>() const { return ToSpan(); }

      public:
        static usz Length(const char* str);
    };
}
