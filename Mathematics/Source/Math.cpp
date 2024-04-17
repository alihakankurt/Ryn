#include <Ryn/Mathematics/Math.hpp>

#include <math.h>

namespace Ryn::Math::Internal
{
    f32 Sqrt(f32 value) noexcept
    {
        return sqrtf(value);
    }

    f64 Sqrt(f64 value) noexcept
    {
        return sqrt(value);
    }
}
