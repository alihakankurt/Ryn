#ifndef __RYN_CORE_STRING_HPP__
#define __RYN_CORE_STRING_HPP__

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    class string
    {
      private:
        usize _length;
        char* _data;

      public:
        string();
        string(cstring str);
        string(const string& other);
        string(string&& other) noexcept;
        ~string();

        string& operator=(const string& other);
        string& operator=(string&& other) noexcept;

        bool operator==(const string& other) const;
        bool operator!=(const string& other) const;

        char operator[](usize index) const;

        string operator+(const string& other) const;
        string& operator+=(const string& other);

        usize Length() const;
        cstring Data() const;

        static usize Length(cstring str);
    };
}

#endif