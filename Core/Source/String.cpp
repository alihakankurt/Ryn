#include <Ryn/Core/String.hpp>
#include <Ryn/Core/Casts.hpp>
#include <Ryn/Core/Memory.hpp>

namespace Ryn
{
    string::string()
    {
        _length = 0;
        _data = nullptr;
    }

    string::string(cstring str)
    {
        _length = string::Length(str);

        _data = new char[_length];
        Memory::Copy(_data, str, _length);
    }

    string::string(const string& other)
    {
        _length = other._length;
        _data = new char[_length];
        Memory::Copy(_data, other._data, _length);
    }

    string::string(string&& other) noexcept
    {
        _length = other._length;
        _data = other._data;
        other._length = 0;
        other._data = nullptr;
    }

    string::~string()
    {
        delete[] _data;
    }

    string& string::operator=(const string& other)
    {
        if (this == &other)
            return *this;

        delete[] _data;

        _length = other._length;
        _data = new char[_length];
        Memory::Copy(_data, other._data, _length);

        return *this;
    }

    string& string::operator=(string&& other) noexcept
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

    bool string::operator==(const string& other) const
    {
        if (_length != other._length)
            return false;

        usize length = _length;
        usize* selfData = As<usize*>(_data);
        usize* otherData = As<usize*>(other._data);

        while (length >= sizeof(usize))
        {
            if (*selfData != *otherData)
                return false;

            selfData += 1;
            otherData += 1;
            length -= sizeof(usize);
        }

        char* selfCharData = As<char*>(selfData);
        char* otherCharData = As<char*>(otherData);

        while (length > 0)
        {
            if (*selfCharData != *otherCharData)
                return false;

            selfCharData += 1;
            otherCharData += 1;
            length -= 1;
        }

        return true;
    }

    bool string::operator!=(const string& other) const
    {
        return !(*this == other);
    }

    char string::operator[](usize index) const
    {
        return _data[index];
    }

    string string::operator+(const string& other) const
    {
        string result = *this;
        result += other;
        return result;
    }

    string& string::operator+=(const string& other)
    {
        usize newLength = _length + other._length;
        char* newData = new char[newLength];

        Memory::Copy(newData, _data, _length);
        Memory::Copy(newData + _length, other._data, other._length);

        delete[] _data;

        _length = newLength;
        _data = newData;

        return *this;
    }

    usize string::Length() const
    {
        return _length;
    }

    cstring string::Data() const
    {
        return _data;
    }

    usize string::Length(cstring str)
    {
        usize length = 0;
        while (str[length] != '\0')
            length++;

        return length;
    }
}
