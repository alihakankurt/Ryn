#include <Ryn/Core/Clock.hpp>

#include <mach/mach_time.h>

namespace Ryn
{
    Time Clock::Now()
    {
        static f64 timebaseFactor = 0_f64;
        if (timebaseFactor == 0_f64)
        {
            mach_timebase_info_data_t timebase;
            mach_timebase_info(&timebase);
            timebaseFactor = static_cast<f64>(timebase.numer) / timebase.denom;
        }

        f64 nanoseconds = mach_absolute_time() * timebaseFactor;
        return Time{nanoseconds};
    }
}
