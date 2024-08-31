#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Core
{
    class String
    {
      private:
        usz _length;
        char* _data;

      public:
        String();
        String(const char* str);
        String(const String& other);
        String(String&& other) noexcept;
        ~String();

        String& operator=(const String& other);
        String& operator=(String&& other) noexcept;

        usz Length() const;
        const char* Data() const;

        char operator[](usz index) const;
        char& operator[](usz index);

        void Append(const char c);
        void Append(const char* str);
        void Append(const String& other);

        String& operator+=(const char c);
        String& operator+=(const char* str);
        String& operator+=(const String& other);

        String operator+(const char c) const;
        String operator+(const char* str) const;
        String operator+(const String& other) const;

        void Insert(usz to, const char c);
        void Insert(usz to, const char* str);
        void Insert(usz to, const String& other);

        void Remove(usz at);
        void Remove(usz from, usz to);

      private:
        void Construct(const char* data, usz length);
        void Append(const char* data, usz length);
        void Insert(usz to, const char* data, usz length);

      public:
        static usz Length(const char* str);
    };
}
