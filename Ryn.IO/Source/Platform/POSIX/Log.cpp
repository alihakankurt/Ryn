#include <Ryn/Core/Memory.hpp>
#include <Ryn/IO/Log.hpp>

#include <unistd.h>

namespace Ryn
{
#if RYN_DEBUG
    void Log::UseColor(const Color color)
    {
        if (!isatty(STDOUT_FILENO))
            return;

        switch (color)
        {
            case Color::Reset:   write(STDOUT_FILENO, "\x1B[0m", 4); break;
            case Color::Black:   write(STDOUT_FILENO, "\x1B[30m", 5); break;
            case Color::Red:     write(STDOUT_FILENO, "\x1B[31m", 5); break;
            case Color::Green:   write(STDOUT_FILENO, "\x1B[32m", 5); break;
            case Color::Yellow:  write(STDOUT_FILENO, "\x1B[33m", 5); break;
            case Color::Blue:    write(STDOUT_FILENO, "\x1B[34m", 5); break;
            case Color::Magenta: write(STDOUT_FILENO, "\x1B[35m", 5); break;
            case Color::Cyan:    write(STDOUT_FILENO, "\x1B[36m", 5); break;
            case Color::White:   write(STDOUT_FILENO, "\x1B[37m", 5); break;
        }
    }

    void Log::Write(const Span<const char> span)
    {
        write(STDOUT_FILENO, &span[0], span.Length());
    }
#endif
}
