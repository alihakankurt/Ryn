#include <Ryn/Core/Clock.hpp>
#include <mach/mach_time.h>

namespace Ryn::Core
{
    f32 Clock::Current()
    {
        static mach_timebase_info_data_t timebase;
        if (timebase.denom == 0)
        {
            mach_timebase_info(&timebase);
        }

        return static_cast<f32>(mach_absolute_time() * timebase.numer / timebase.denom) * 1e-9f;
    }
}
