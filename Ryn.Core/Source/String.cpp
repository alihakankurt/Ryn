#include <Ryn/Core/String.hpp>

namespace Ryn::Core
{
    String::String()
    {
        _length = 0;
        _data = nullptr;
    }

    String::String(const char* str) :
        String()
    {
        Construct(str, String::Length(str));
    }

    String::String(const String& other) :
        String()
    {
        Construct(other._data, other._length);
    }

    String::String(String&& other) noexcept
    {
        _length = other._length;
        _data = other._data;
        other._length = 0;
        other._data = nullptr;
    }

    String::~String()
    {
        delete[] _data;
        _data = nullptr;
    }

    String& String::operator=(const String& other)
    {
        if (this != &other)
        {
            Construct(other._data, other._length);
        }

        return *this;
    }

    String& String::operator=(String&& other) noexcept
    {
        if (this != &other)
        {
            delete[] _data;
            _length = other._length;
            _data = other._data;
            other._length = 0;
            other._data = nullptr;
        }

        return *this;
    }

    usz String::Length() const
    {
        return _length;
    }

    const char* String::Data() const
    {
        return _data;
    }

    char String::operator[](usz index) const
    {
        return _data[index];
    }

    char& String::operator[](usz index)
    {
        return _data[index];
    }

    void String::Append(const char c)
    {
        Append(&c, 1);
    }

    void String::Append(const char* str)
    {
        Append(str, String::Length(str));
    }

    void String::Append(const String& other)
    {
        Append(other._data, other._length);
    }

    String& String::operator+=(const char c)
    {
        Append(c);
        return *this;
    }

    String& String::operator+=(const char* str)
    {
        Append(str);
        return *this;
    }

    String& String::operator+=(const String& other)
    {
        Append(other);
        return *this;
    }

    String String::operator+(const char c)
    {
        String result = *this;
        result += c;
        return result;
    }

    String String::operator+(const char* str)
    {
        String result = *this;
        result += str;
        return result;
    }

    String String::operator+(const String& other)
    {
        String result = *this;
        result += other;
        return result;
    }

    void String::Insert(usz to, const char c)
    {
        Insert(to, &c, 1);
    }

    void String::Insert(usz to, const char* str)
    {
        Insert(to, str, String::Length(str));
    }

    void String::Insert(usz to, const String& other)
    {
        Insert(to, other._data, other._length);
    }

    void String::Remove(usz at)
    {
        Remove(at, at);
    }

    void String::Remove(usz from, usz to)
    {
        if (from >= _length)
        {
            return;
        }

        if (to >= _length)
        {
            to = _length - 1;
        }

        if (from > to)
        {
            return;
        }

        usz newLength = _length - (to - from + 1);
        char* newData = new char[newLength + 1];

        for (usz index = 0; index < from; index += 1)
        {
            newData[index] = _data[index];
        }

        for (usz index = to + 1; index < _length; index += 1)
        {
            newData[index - (to - from + 1)] = _data[index];
        }

        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;
    }

    void String::Construct(const char* data, usz length)
    {
        delete[] _data;

        _length = length;
        _data = new char[_length + 1];
        for (usz index = 0; index < _length; index += 1)
        {
            _data[index] = data[index];
        }

        _data[_length] = '\0';
    }

    void String::Append(const char* data, usz length)
    {
        usz newLength = _length + length;
        char* newData = new char[newLength + 1];

        for (usz index = 0; index < _length; index += 1)
        {
            newData[index] = _data[index];
        }

        for (usz index = 0; index < length; index += 1)
        {
            newData[_length + index] = data[index];
        }

        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;
    }

    void String::Insert(usz to, const char* data, usz length)
    {
        if (to >= _length)
        {
            Append(data, length);
            return;
        }

        usz newLength = _length + length;
        char* newData = new char[newLength + 1];

        for (usz index = 0; index < to; index += 1)
        {
            newData[index] = _data[index];
        }

        for (usz index = 0; index < length; index += 1)
        {
            newData[index + to] = data[index];
        }

        for (usz index = to; index < _length; index += 1)
        {
            newData[index + length] = _data[index];
        }

        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;
    }

    usz String::Length(const char* str)
    {
        usz length = 0;
        while (str[length] != '\0')
        {
            length += 1;
        }

        return length;
    }
}
