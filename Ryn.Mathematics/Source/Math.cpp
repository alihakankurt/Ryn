#include <Ryn/Mathematics/Math.hpp>

#include <math.h>

namespace Ryn::Private::Math
{
    f32 FloorImpl(f32 value) { return floorf(value); }
    f64 FloorImpl(f64 value) { return floor(value); }

    f32 CeilImpl(f32 value) { return ceilf(value); }
    f64 CeilImpl(f64 value) { return ceil(value); }

    f32 SqrtImpl(f32 value) { return sqrtf(value); }
    f64 SqrtImpl(f64 value) { return sqrt(value); }

    f32 PowImpl(f32 base, f32 exponent) { return powf(base, exponent); }
    f64 PowImpl(f64 base, f64 exponent) { return pow(base, exponent); }

    f32 SinImpl(f32 value) { return sinf(value); }
    f64 SinImpl(f64 value) { return sin(value); }

    f32 CosImpl(f32 value) { return cosf(value); }
    f64 CosImpl(f64 value) { return cos(value); }

    f32 TanImpl(f32 value) { return tanf(value); }
    f64 TanImpl(f64 value) { return tan(value); }

    f32 AsinImpl(f32 value) { return asinf(value); }
    f64 AsinImpl(f64 value) { return asin(value); }

    f32 AcosImpl(f32 value) { return acosf(value); }
    f64 AcosImpl(f64 value) { return acos(value); }

    f32 AtanImpl(f32 value) { return atanf(value); }
    f64 AtanImpl(f64 value) { return atan(value); }

    f32 Atan2Impl(f32 y, f32 x) { return atan2f(y, x); }
    f64 Atan2Impl(f64 y, f64 x) { return atan2(y, x); }

    f32 SinhImpl(f32 value) { return sinhf(value); }
    f64 SinhImpl(f64 value) { return sinh(value); }

    f32 CoshImpl(f32 value) { return coshf(value); }
    f64 CoshImpl(f64 value) { return cosh(value); }

    f32 TanhImpl(f32 value) { return tanhf(value); }
    f64 TanhImpl(f64 value) { return tanh(value); }

    f32 AsinhImpl(f32 value) { return asinhf(value); }
    f64 AsinhImpl(f64 value) { return asinh(value); }

    f32 AcoshImpl(f32 value) { return acoshf(value); }
    f64 AcoshImpl(f64 value) { return acosh(value); }

    f32 AtanhImpl(f32 value) { return atanhf(value); }
    f64 AtanhImpl(f64 value) { return atanh(value); }

    f32 LogImpl(f32 value) { return logf(value); }
    f64 LogImpl(f64 value) { return log(value); }

    f32 Log2Impl(f32 value) { return log2f(value); }
    f64 Log2Impl(f64 value) { return log2(value); }

    f32 Log10Impl(f32 value) { return log10f(value); }
    f64 Log10Impl(f64 value) { return log10(value); }

    f32 ExpImpl(f32 value) { return expf(value); }
    f64 ExpImpl(f64 value) { return exp(value); }
}
