#include <Ryn/Core/String.hpp>
#include <Ryn/Core/Memory.hpp>

namespace Ryn::Core
{
    String::String(const String& other)
    {
        Construct(other._data, other._length);
    }

    String::String(String&& other) :
        _length(other._length),
        _data(other._data)
    {
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

        Memory::Copy(&_data[0], &data[0], _length);
        _data[_length] = '\0';
    }

    String& String::Append(const char* data, usz length)
    {
        usz newLength = _length + length;
        char* newData = new char[newLength + 1];

        Memory::Copy(&newData[0], &_data[0], _length);
        Memory::Copy(&newData[_length], &data[0], length);
        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;

        return *this;
    }

    String& String::Insert(usz to, const char* data, usz length)
    {
        if (to >= _length)
        {
            return Append(data, length);
        }

        usz newLength = _length + length;
        char* newData = new char[newLength + 1];

        Memory::Copy(&newData[0], &_data[0], to);
        Memory::Copy(&newData[to], &data[0], length);
        Memory::Copy(&newData[to + length], &_data[to], _length - to);
        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;

        return *this;
    }

    String& String::Remove(usz from, usz to)
    {
        if (from >= _length || to >= _length || from > to)
            return *this;

        usz newLength = _length - (to - from + 1);
        char* newData = new char[newLength + 1];

        Memory::Copy(&newData[0], &_data[0], from);
        Memory::Copy(&newData[from], &_data[to + 1], _length - to - 1);
        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;

        return *this;
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
