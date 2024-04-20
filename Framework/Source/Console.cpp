#include <Ryn/Framework/Console.hpp>
#include <Ryn/Native/Platform.hpp>

namespace Ryn
{
    static constexpr usize BufferSize = 64;
    static char Buffer[BufferSize];

    static constexpr usize WriteInteger(u64 value, usize index, isize padding = 0)
    {
        if (value == 0 && padding <= 1)
        {
            Buffer[index] = '0';
            return index - 1;
        }

        while (value > 0)
        {
            Buffer[index] = '0' + As<char>(value % 10);
            index -= 1;
            value /= 10;
            padding -= 1;
        }
    
        while (padding > 0)
        {
            Buffer[index] = '0';
            index -= 1;
            padding -= 1;
        }

        return index;
    }

    static constexpr usize WriteSign(bool negative, usize index)
    {
        if (negative)
        {
            Buffer[index] = '-';
            index -= 1;
        }
        return index;
    }

    bool Console::Write(char value)
    {
        return Platform::Write(&value, 1);
    }

    bool Console::Write(cstring value)
    {
        return Platform::Write(value, string::Length(value));
    }

    bool Console::Write(const string& value)
    {
        return Platform::Write(value.Data(), value.Length());
    }

    bool Console::Write(i8 value)
    {
        return Write(As<i64>(value));
    }

    bool Console::Write(i16 value)
    {
        return Write(As<i64>(value));
    }

    bool Console::Write(i32 value)
    {
        return Write(As<i64>(value));
    }

    bool Console::Write(i64 value)
    {
        usize index = BufferSize - 1;
        bool negative = value < 0;
        value = negative ? -value : value;
        index = WriteInteger(As<u64>(value), index);
        index = WriteSign(negative, index);
        return Platform::Write(Buffer + index + 1, BufferSize - index - 1);
    }

    bool Console::Write(u8 value)
    {
        return Write(As<u64>(value));
    }

    bool Console::Write(u16 value)
    {
        return Write(As<u64>(value));
    }

    bool Console::Write(u32 value)
    {
        return Write(As<u64>(value));
    }

    bool Console::Write(u64 value)
    {
        usize index = BufferSize - 1;
        index = WriteInteger(value, index);
        return Platform::Write(Buffer + index + 1, BufferSize - index - 1);
    }

    bool Console::Write(f32 value)
    {
        return Write(As<f64>(value));
    }

    bool Console::Write(f64 value)
    {
        usize index = BufferSize - 1;
        bool negative = value < 0;

        i64 integer = As<i64>(value);
        u64 fraction = As<u64>(((value - As<f64>(integer)) * 1e7 + 0.5) / 1e1);

        index = WriteInteger(fraction, index, 6);

        Buffer[index] = '.';
        index -= 1;

        integer = negative ? -integer : integer;
        index = WriteInteger(As<u64>(integer), index);
        index = WriteSign(negative, index);

        return Platform::Write(Buffer + index + 1, BufferSize - index - 1);
    }
}
