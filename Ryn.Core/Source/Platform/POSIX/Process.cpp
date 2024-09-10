#include <Ryn/Core/Process.hpp>
#include <unistd.h>

namespace Ryn
{
    void Process::Exit(int code)
    {
        _exit(code);
    }
}
