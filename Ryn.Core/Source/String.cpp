#include <Ryn/Core/String.hpp>

namespace Ryn
{
    String::~String()
    {
        delete[] _data;
        _data = {};
        _length = {};
    }

    String& String::operator=(const String& other)
    {
        if (this != &other)
        {
            delete[] _data;
            Construct(other._data, other._length);
        }
        return *this;
    }

    String& String::operator=(String&& other)
    {
        if (this != &other)
        {
            delete[] _data;
            _data = Utility::Exchange(other._data);
            _length = Utility::Exchange(other._length);
        }
        return *this;
    }

    void String::Construct(const char* data, usz length)
    {
        _data = new char[length + 1];
        Memory::Copy(&_data[0], &data[0], length);
        _data[length] = '\0';

        _length = length;
    }

    String& String::Append(const char* data, usz length)
    {
        usz newLength = _length + length;
        char* newData = new char[newLength + 1];

        Memory::Copy(&newData[0], &_data[0], _length);
        Memory::Copy(&newData[_length], &data[0], length);
        newData[newLength] = '\0';

        delete[] _data;
        _data = newData;
        _length = newLength;
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
        _data = newData;
        _length = newLength;
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
        _data = newData;
        _length = newLength;
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

    Span<char> String::Format(Span<char> span, bool value)
    {
        if (value && span.Length() >= 4)
        {
            span[0] = 't';
            span[1] = 'r';
            span[2] = 'u';
            span[3] = 'e';
            return span.Slice(0, 4);
        }
        else if (!value && span.Length() >= 5)
        {
            span[0] = 'f';
            span[1] = 'a';
            span[2] = 'l';
            span[3] = 's';
            span[4] = 'e';
            return span.Slice(0, 5);
        }
        else
        {
            return {};
        }
    }

    Span<char> String::Format(Span<char> span, i64 value)
    {
        if (span.Length() == 0)
            return {};

        usz length = 0;
        if (value < 0)
        {
            span[length] = '-';
            length += 1;
            value = -value;
        }

        Span<char> integerPart = String::Format(span.Slice(length), static_cast<u64>(value));
        length += integerPart.Length();
        return span.Slice(0, length);
    }

    Span<char> String::Format(Span<char> span, u64 value)
    {
        if (span.Length() == 0)
            return {};

        usz length = 0;
        do
        {
            span[length] = static_cast<char>('0' + (value % 10));
            length += 1;
            value /= 10;
        }
        while (value != 0 && length < span.Length());

        Memory::Reverse(span.Data(), length);
        return span.Slice(0, length);
    }

    Span<char> String::Format(Span<char> span, f64 value)
    {
        i64 integer = static_cast<i64>(value);
        f64 fraction = value - integer;
        fraction = (fraction < 0) ? -fraction : fraction;

        constexpr u64 precision = 1e6;
        fraction *= precision;

        Span<char> integerPart = String::Format(span, integer);
        usz length = integerPart.Length();

        if (length >= span.Length())
            return span.Slice(0, length);

        span[length] = '.';
        length += 1;

        Span<char> fractionPart = String::Format(span.Slice(integerPart.Length() + 1), static_cast<u64>(fraction));
        length += fractionPart.Length();

        return span.Slice(0, length);
    }
}
