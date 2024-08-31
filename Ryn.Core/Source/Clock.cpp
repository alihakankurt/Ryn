#include <Ryn/Core/Clock.hpp>

namespace Ryn::Core
{
    Clock::Clock()
    {
        _start = Current();
    }

    f32 Clock::Restart()
    {
        f32 current = Current();
        f32 elapsed = current - _start;
        _start = current;
        return elapsed;
    }
}
