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

    f32 Pow(f32 base, f32 exponent)
    {
        return powf(base, exponent);
    }

    f64 Pow(f64 base, f64 exponent)
    {
        return pow(base, exponent);
    }

    f32 Exp(f32 value)
    {
        return expf(value);
    }

    f64 Exp(f64 value)
    {
        return exp(value);
    }

    f32 Log(f32 value)
    {
        return logf(value);
    }

    f64 Log(f64 value)
    {
        return log(value);
    }

    f32 Log(f32 value, f32 base)
    {
        return logf(value) / logf(base);
    }

    f64 Log(f64 value, f64 base)
    {
        return log(value) / log(base);
    }

    f32 Log2(f32 value)
    {
        return log2f(value);
    }

    f64 Log2(f64 value)
    {
        return log2(value);
    }

    f32 Log10(f32 value)
    {
        return log10f(value);
    }

    f64 Log10(f64 value)
    {
        return log10(value);
    }

    f32 Sin(f32 value)
    {
        return sinf(value);
    }

    f64 Sin(f64 value)
    {
        return sin(value);
    }

    f32 Cos(f32 value)
    {
        return cosf(value);
    }

    f64 Cos(f64 value)
    {
        return cos(value);
    }

    f32 Tan(f32 value)
    {
        return tanf(value);
    }

    f64 Tan(f64 value)
    {
        return tan(value);
    }

    f32 Asin(f32 value)
    {
        return asinf(value);
    }

    f64 Asin(f64 value)
    {
        return asin(value);
    }

    f32 Acos(f32 value)
    {
        return acosf(value);
    }

    f64 Acos(f64 value)
    {
        return acos(value);
    }

    f32 Atan(f32 value)
    {
        return atanf(value);
    }

    f64 Atan(f64 value)
    {
        return atan(value);
    }

    f32 Atan2(f32 y, f32 x)
    {
        return atan2f(y, x);
    }

    f64 Atan2(f64 y, f64 x)
    {
        return atan2(y, x);
    }

    f32 Sinh(f32 value)
    {
        return sinhf(value);
    }

    f64 Sinh(f64 value)
    {
        return sinh(value);
    }

    f32 Cosh(f32 value)
    {
        return coshf(value);
    }

    f64 Cosh(f64 value)
    {
        return cosh(value);
    }

    f32 Tanh(f32 value)
    {
        return tanhf(value);
    }

    f64 Tanh(f64 value)
    {
        return tanh(value);
    }

    f32 Asinh(f32 value)
    {
        return asinhf(value);
    }

    f64 Asinh(f64 value)
    {
        return asinh(value);
    }

    f32 Acosh(f32 value)
    {
        return acoshf(value);
    }

    f64 Acosh(f64 value)
    {
        return acosh(value);
    }

    f32 Atanh(f32 value)
    {
        return atanhf(value);
    }

    f64 Atanh(f64 value)
    {
        return atanh(value);
    }
}
