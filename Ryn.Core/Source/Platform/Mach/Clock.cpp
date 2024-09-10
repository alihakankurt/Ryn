#include <Ryn/Core/Clock.hpp>
#include <mach/mach_time.h>

namespace Ryn
{
    Time Clock::Now()
    {
        static f64 SecondsPerTick = 0_f64;
        if (SecondsPerTick == 0_f64)
        {
            mach_timebase_info_data_t timebase;
            mach_timebase_info(&timebase);
            SecondsPerTick = static_cast<f64>(timebase.numer) / timebase.denom * 1e-9_f64;
        }

        return Time{mach_absolute_time() * SecondsPerTick};
    }
}
