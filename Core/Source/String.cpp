#include <Ryn/Core/String.hpp>

namespace Ryn
{
    string::string()
    {
        _length = 0;
        _data = nullptr;
    }

    string::string(const char* str)
    {
        _length = string::Length(str);

        _data = new char[_length];
        for (usize i = 0; i < _length; i++)
            _data[i] = str[i];
    }

    string::string(const string& other)
    {
        _length = other._length;
        _data = new char[_length];
        for (usize i = 0; i < _length; i++)
            _data[i] = other._data[i];
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
        for (usize i = 0; i < _length; i++)
            _data[i] = other._data[i];

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

        for (usize i = 0; i < _length; i++)
            if (_data[i] != other._data[i])
                return false;

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
        char* temp = _data;
        _data = new char[_length + other._length];

        for (usize i = 0; i < _length; i++)
            _data[i] = temp[i];

        for (usize i = 0; i < other._length; i++)
            _data[_length + i] = other._data[i];

        _length += other._length;

        delete[] temp;

        return *this;
    }

    usize string::Length() const
    {
        return _length;
    }

    const char* string::Data() const
    {
        return _data;
    }

    usize string::Length(const char* str)
    {
        usize length = 0;
        while (str[length] != '\0')
            length++;

        return length;
    }
}
