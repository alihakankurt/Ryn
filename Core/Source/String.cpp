#include <Ryn/Core/String.hpp>
#include <Ryn/Core/Casts.hpp>
#include <Ryn/Core/Memory.hpp>

namespace Ryn
{
    String::String(const char* str)
    {
        _length = String::Length(str);
        _data = new char[_length + 1];

        Memory::Copy(_data, str, _length);
        _data[_length] = '\0';
    }

    String::String(char* str, usize length)
    {
        _length = length;
        _data = str;
    }

    String::String(const String& other)
    {
        _length = other._length;
        _data = new char[_length + 1];

        Memory::Copy(_data, other._data, _length);
        _data[_length] = '\0';
    }

    String::String(String&& other)
    {
        _length = other._length;
        _data = other._data;

        other._length = 0;
        other._data = nullptr;
    }

    String::~String()
    {
        delete[] _data;
    }

    String& String::operator=(const String& other)
    {
        if (this == &other)
            return *this;

        delete[] _data;

        _length = other._length;
        _data = new char[_length + 1];

        Memory::Copy(_data, other._data, _length);
        _data[_length] = '\0';

        return *this;
    }

    String& String::operator=(String&& other)
    {
        if (this == &other)
            return *this;

        delete[] _data;

        _length = other._length;
        _data = other._data;

        other._length = 0;
        other._data = nullptr;

        return *this;
    }

    char String::operator[](usize index) const
    {
        return (0 <= index && index < _length) ? _data[index] : '\0';
    }

    usize String::Length() const
    {
        return _length;
    }

    const char* String::Data() const
    {
        return _data;
    }

    const char* String::Begin() const
    {
        return _data;
    }

    const char* String::End() const
    {
        return _data + _length;
    }

    bool String::operator==(const char* other) const
    {
        usize length = String::Length(other);
        return _length == length == String::Compare(_data, other, length);
    }

    bool String::operator==(const String& other) const
    {
        return _length == other._length == String::Compare(_data, other._data, other._length);
    }

    bool String::operator!=(const char* other) const
    {
        return !(*this == other);
    }

    bool String::operator!=(const String& other) const
    {
        return !(*this == other);
    }

    String String::operator+(const char c) const
    {
        String result = *this;
        result += c;
        return result;
    }

    String String::operator+(const char* other) const
    {
        String result = *this;
        result += other;
        return result;
    }

    String String::operator+(const String& other) const
    {
        String result = *this;
        result += other;
        return result;
    }

    String& String::operator+=(const char c)
    {
        _length = String::Extend(_data, _length, &c, 1);
        return *this;
    }

    String& String::operator+=(const char* other)
    {
        _length = String::Extend(_data, _length, other, String::Length(other));
        return *this;
    }

    String& String::operator+=(const String& other)
    {
        _length = String::Extend(_data, _length, other._data, other._length);
        return *this;
    }

    usize String::Length(const char* str)
    {
        usize length = 0;
        while (str[length] != '\0')
            length++;

        return length;
    }

    bool String::Compare(const char* str1, const char* str2, usize length)
    {
        auto data1 = As<const usize*>(str1);
        auto data2 = As<const usize*>(str2);

        while (length >= sizeof(usize))
        {
            if (*data1 != *data2)
                return false;

            data1 += 1;
            data2 += 1;
            length -= sizeof(usize);
        }

        auto charData1 = As<const char*>(data1);
        auto charData2 = As<const char*>(data2);

        while (length > 0)
        {
            if (*charData1 != *charData2)
                return false;

            charData1 += 1;
            charData2 += 1;
            length -= 1;
        }

        return true;
    }

    usize String::Extend(char*& self, usize length, const char* other, usize otherLength)
    {
        usize totalLength = length + otherLength;
        auto data = new char[totalLength + 1];

        Memory::Copy(data, self, length);
        Memory::Copy(data + length, other, otherLength);
        data[totalLength] = '\0';

        delete[] self;
        self = data;

        return totalLength;
    }
}
