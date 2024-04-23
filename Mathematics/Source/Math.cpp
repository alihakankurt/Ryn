#include <Ryn/Mathematics/Math.hpp>

#include <math.h>

namespace Ryn::Math::Internal
{
    f32 Sqrt(f32 value)
    {
        return sqrtf(value);
    }

    f64 Sqrt(f64 value)
    {
        return sqrt(value);
    }
}
