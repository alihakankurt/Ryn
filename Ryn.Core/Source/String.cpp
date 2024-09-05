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

    void String::Construct(const char* data, u32 length)
    {
        delete[] _data;

        _length = length;
        _data = new char[_length + 1];

        Memory::Copy(&_data[0], &data[0], _length);
        _data[_length] = '\0';
    }

    String& String::Append(const char* data, u32 length)
    {
        u32 newLength = _length + length;
        char* newData = new char[newLength + 1];

        Memory::Copy(&newData[0], &_data[0], _length);
        Memory::Copy(&newData[_length], &data[0], length);
        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;

        return *this;
    }

    String& String::Insert(u32 to, const char* data, u32 length)
    {
        if (to >= _length)
        {
            return Append(data, length);
        }

        u32 newLength = _length + length;
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

    String& String::Remove(u32 from, u32 to)
    {
        if (from >= _length || to >= _length || from > to)
            return *this;

        u32 newLength = _length - (to - from + 1);
        char* newData = new char[newLength + 1];

        Memory::Copy(&newData[0], &_data[0], from);
        Memory::Copy(&newData[from], &_data[to + 1], _length - to - 1);
        newData[newLength] = '\0';

        delete[] _data;

        _length = newLength;
        _data = newData;

        return *this;
    }

    u32 String::Length(const char* str)
    {
        u32 length = 0;
        while (str[length] != '\0')
        {
            length += 1;
        }

        return length;
    }

    Span<const char> String::Format(Span<char> buffer, i64 value)
    {
        if (value < 0)
        {
            buffer[0] = '-';
            value = -value;
        }

        Span<const char> result = String::Format(buffer.Slice(1), static_cast<u64>(value));
        return Span<const char>(&buffer[0], result.Length() + 1);
    }

    Span<const char> String::Format(Span<char> buffer, u64 value)
    {
        u32 index = 0;
        do
        {
            buffer[index] = static_cast<char>('0' + (value % 10));
            index += 1;
            value /= 10;
        }
        while (value != 0 && index < buffer.Length());

        Memory::Reverse(&buffer[0], index);
        return Span<const char>(&buffer[0], index);
    }

    Span<const char> String::Format(Span<char> buffer, f64 value, u64 precision)
    {
        i64 integer = static_cast<i64>(value);
        f64 fraction = value - integer;
        fraction = (fraction < 0) ? -fraction : fraction;
        fraction *= precision;

        Span<const char> integerPart = String::Format(buffer, integer);
        buffer[integerPart.Length()] = '.';
        Span<const char> fractionPart = String::Format(buffer.Slice(integerPart.Length() + 1), static_cast<u64>(fraction));

        return Span<const char>(&buffer[0], integerPart.Length() + 1 + fractionPart.Length());
    }
}
