#include <Ryn/Core/Clock.hpp>

namespace Ryn
{
    Clock::Clock()
    {
        _start = Current();
    }

    f64 Clock::Restart()
    {
        f64 current = Current();
        f64 elapsed = current - _start;
        _start = current;
        return elapsed;
    }
}
