#include <Ryn/Core/Clock.hpp>
#include <mach/mach_time.h>

namespace Ryn::Core
{
    f64 Clock::Current()
    {
        static f64 SecondsPerTick = 0.0;
        if (SecondsPerTick == 0.0)
        {
            mach_timebase_info_data_t timebase;
            mach_timebase_info(&timebase);
            SecondsPerTick = static_cast<f64>(timebase.numer) / timebase.denom * 1e-9;
        }

        return mach_absolute_time() * SecondsPerTick;
    }
}
