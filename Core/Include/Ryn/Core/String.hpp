#ifndef __RYN_CORE_STRING_HPP__
#define __RYN_CORE_STRING_HPP__

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    class String
    {
      private:
        usize _length;
        char* _data;

      public:
        inline constexpr String() = default;
        String(const char* str);
        String(char* str, usize length);
        String(const String& other);
        String(String&& other);
        ~String();

        String& operator=(const String& other);
        String& operator=(String&& other);

        char operator[](usize index) const;
        usize Length() const;
        const char* Data() const;

        const char* Begin() const;
        const char* End() const;

        bool operator==(const char* other) const;
        bool operator==(const String& other) const;

        bool operator!=(const char* other) const;
        bool operator!=(const String& other) const;

        String operator+(const char c) const;
        String operator+(const char* str) const;
        String operator+(const String& other) const;

        String& operator+=(const char c);
        String& operator+=(const char* str);
        String& operator+=(const String& other);

      public:
        static usize Length(const char* str);
        static bool Compare(const char* str1, const char* str2, usize length);
        static usize Extend(char*& self, usize length, const char* other, usize otherLength);
    };

    using string = String;
}

#endif