#include <Ryn/Framework/Console.hpp>
#include <Ryn/Native/Platform.hpp>

namespace Ryn
{
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
        static constexpr usize bufferSize = 32;
        static char buffer[bufferSize];

        bool negative = value < 0;
        usize index = bufferSize - 1;
        while (value != 0)
        {
            buffer[index] = '0' + As<char>(value % 10);
            index -= 1;
            value /= 10;
        }

        if (negative)
        {
            buffer[index] = '-';
            index -= 1;
        }

        return Platform::Write(buffer + index + 1, bufferSize - index - 1);
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
        static constexpr usize bufferSize = 32;
        static char buffer[bufferSize];

        usize index = bufferSize - 1;
        while (value != 0)
        {
            buffer[index] = '0' + As<char>(value % 10);
            index -= 1;
            value /= 10;
        }

        return Platform::Write(buffer + index + 1, bufferSize - index - 1);
    }

    bool Console::Write(f32 value)
    {
        return Write(As<f64>(value));
    }

    bool Console::Write(f64 value)
    {
        static constexpr usize bufferSize = 64;
        static char buffer[bufferSize];

        bool negative = value < 0;
        usize index = bufferSize - 1;

        i64 integer = As<i64>(value);
        f64 fraction = value - As<f64>(integer);

        while (fraction > 0.0)
        {
            fraction *= 10.0;
            buffer[index] = '0' + As<char>(fraction);
            index -= 1;
            fraction -= As<f64>(As<u64>(fraction));
        }

        buffer[index] = '.';

        while (integer != 0)
        {
            buffer[index] = '0' + (integer % 10);
            index -= 1;
            integer /= 10;
        }

        if (negative)
        {
            buffer[index] = '-';
            index -= 1;
        }

        return Platform::Write(buffer + index + 1, bufferSize - index - 1);
    }
}
