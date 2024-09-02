#include <Ryn/Core/String.hpp>
#include <Ryn/Core/Memory.hpp>

namespace Ryn::Core
{
    String::String(const Span<char>& span)
    {
        Construct(&span[0], span.Length());
    }

    String::String(const String& other)
    {
        Construct(other._data, other._length);
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

    String& String::operator=(String&& other)
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

    void String::Construct(const char* data, usz length)
    {
        delete[] _data;

        _length = length;
        _data = new char[_length + 1];

        Memory::Copy(&_data[0], &data[0], _length * sizeof(char));
        _data[_length] = '\0';
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

    void String::Append(const char* data, usz length)
    {
        usz newLength = _length + length;
        char* newData = new char[newLength + 1];

        Memory::Copy(&newData[0], &_data[0], _length * sizeof(char));
        Memory::Copy(&newData[_length], &data[0], length * sizeof(char));
        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;
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

    String String::operator+(const char c) const
    {
        String result = *this;
        result += c;
        return result;
    }

    String String::operator+(const char* str) const
    {
        String result = *this;
        result += str;
        return result;
    }

    String String::operator+(const String& other) const
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

    void String::Insert(usz to, const char* data, usz length)
    {
        if (to >= _length)
        {
            Append(data, length);
            return;
        }

        usz newLength = _length + length;
        char* newData = new char[newLength + 1];

        Memory::Copy(&newData[0], &_data[0], to * sizeof(char));
        Memory::Copy(&newData[to], &data[0], length * sizeof(char));
        Memory::Copy(&newData[to + length], &_data[to], (_length - to) * sizeof(char));
        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;
    }

    void String::Remove(usz at)
    {
        Remove(at, at);
    }

    void String::Remove(usz from, usz to)
    {
        if (from >= _length || to >= _length || from > to)
            return;

        usz newLength = _length - (to - from + 1);
        char* newData = new char[newLength + 1];

        Memory::Copy(&newData[0], &_data[0], from * sizeof(char));
        Memory::Copy(&newData[from], &_data[to + 1], (_length - to - 1) * sizeof(char));
        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;
    }

    bool String::operator==(const String& other) const
    {
        return _length == other._length && Memory::Compare(_data, other._data, _length * sizeof(char)) == 0;
    }

    bool String::operator!=(const String& other) const
    {
        return !(*this == other);
    }

    bool String::operator<(const String& other) const
    {
        const usz length = (_length < other._length) ? _length : other._length;
        const isz comparison = Memory::Compare(_data, other._data, length * sizeof(char));
        return (comparison == 0) ? _length < other._length : comparison < 0;
    }

    bool String::operator>(const String& other) const
    {
        const usz length = (_length < other._length) ? _length : other._length;
        const isz comparison = Memory::Compare(_data, other._data, length * sizeof(char));
        return (comparison == 0) ? _length > other._length : comparison > 0;
    }

    bool String::operator<=(const String& other) const
    {
        return !(*this > other);
    }

    bool String::operator>=(const String& other) const
    {
        return !(*this < other);
    }

    Span<char> String::ToSpan() const
    {
        return Span<char>(_data, _length);
    }

    Span<char> String::ToSpan(usz start) const
    {
        return ToSpan().Cut(start);
    }

    Span<char> String::ToSpan(usz start, usz length) const
    {
        return ToSpan().Cut(start, length);
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
