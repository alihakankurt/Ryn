#include <Ryn/Core/String.hpp>

namespace Ryn
{
    void String::Create(usz length, const char* data)
    {
        _length = length;
        _data = Memory::Allocate<char>(_length + 1);
        Memory::Copy(_data, data, _length);
        _data[_length] = '\0';
    }

    void String::Destroy()
    {
        Memory::Free<char>(_data, _length + 1);
        _length = 0;
        _data = {};
    }

    String& String::Append(usz length, const char* data)
    {
        usz newLength = _length + length;
        char* newData = Memory::Allocate<char>(newLength + 1);

        Memory::Copy(newData, _data, _length);
        Memory::Copy(newData + _length, data, length);
        newData[newLength] = '\0';

        Memory::Free<char>(_data, _length + 1);

        _length = newLength;
        _data = newData;
        return *this;
    }

    String& String::Insert(usz to, usz length, const char* data)
    {
        if (to >= _length)
        {
            return Append(length, data);
        }

        usz newLength = _length + length;
        char* newData = Memory::Allocate<char>(newLength + 1);

        Memory::Copy(newData, _data, to);
        Memory::Copy(newData + to, data, length);
        Memory::Copy(newData + to + length, _data + to, _length - to);
        newData[newLength] = '\0';

        Memory::Free<char>(_data, _length + 1);

        _length = newLength;
        _data = newData;
        return *this;
    }

    String& String::Remove(usz from, usz to)
    {
        if (from >= _length || to >= _length || from > to)
            return *this;

        usz newLength = _length - (to - from + 1);
        char* newData = Memory::Allocate<char>(newLength + 1);

        Memory::Copy(newData, _data, from);
        Memory::Copy(newData + from, _data + to + 1, _length - to - 1);
        newData[newLength] = '\0';

        Memory::Free<char>(_data, _length + 1);

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
