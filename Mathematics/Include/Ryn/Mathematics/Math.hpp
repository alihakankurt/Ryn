#ifndef __RYN_MATHEMATICS_MATH_HPP__
#define __RYN_MATHEMATICS_MATH_HPP__

#include <Ryn/Core.hpp>

namespace Ryn::Math::Internal
{
    f32 Sqrt(f32 value);
    f64 Sqrt(f64 value);

    f32 Pow(f32 base, f32 exponent);
    f64 Pow(f64 base, f64 exponent);

    f32 Exp(f32 value);
    f64 Exp(f64 value);

    f32 Log(f32 value);
    f64 Log(f64 value);

    f32 Log(f32 value, f32 base);
    f64 Log(f64 value, f64 base);

    f32 Log2(f32 value);
    f64 Log2(f64 value);

    f32 Log10(f32 value);
    f64 Log10(f64 value);

    f32 Sin(f32 value);
    f64 Sin(f64 value);

    f32 Cos(f32 value);
    f64 Cos(f64 value);

    f32 Tan(f32 value);
    f64 Tan(f64 value);

    f32 Asin(f32 value);
    f64 Asin(f64 value);

    f32 Acos(f32 value);
    f64 Acos(f64 value);

    f32 Atan(f32 value);
    f64 Atan(f64 value);

    f32 Atan2(f32 y, f32 x);
    f64 Atan2(f64 y, f64 x);

    f32 Sinh(f32 value);
    f64 Sinh(f64 value);

    f32 Cosh(f32 value);
    f64 Cosh(f64 value);

    f32 Tanh(f32 value);
    f64 Tanh(f64 value);

    f32 Asinh(f32 value);
    f64 Asinh(f64 value);

    f32 Acosh(f32 value);
    f64 Acosh(f64 value);

    f32 Atanh(f32 value);
    f64 Atanh(f64 value);
}

namespace Ryn
{
    namespace Math
    {
        template <Number TNumber>
        static inline constexpr TNumber Zero = Numeric<TNumber>::Zero;

        template <Number TNumber>
        static inline constexpr TNumber One = Numeric<TNumber>::One;

        template <Number TNumber>
        static inline constexpr TNumber MaxValue = Numeric<TNumber>::MaxValue;

        template <Number TNumber>
        static inline constexpr TNumber MinValue = Numeric<TNumber>::MinValue;

        template <Number TNumber>
        static inline constexpr TNumber Epsilon = Numeric<TNumber>::Epsilon;

        template <Number TNumber>
        static inline constexpr TNumber NaN = Numeric<TNumber>::NaN;

        template <Number TNumber>
        static inline constexpr TNumber PositiveInfinity = Numeric<TNumber>::PositiveInfinity;

        template <Number TNumber>
        static inline constexpr TNumber NegativeInfinity = Numeric<TNumber>::NegativeInfinity;

        template <Number TNumber>
        static inline constexpr TNumber E = Numeric<TNumber>::E;

        template <Number TNumber>
        static inline constexpr TNumber Pi = Numeric<TNumber>::Pi;

        template <Number TNumber>
        static inline constexpr TNumber HalfPi = Numeric<TNumber>::HalfPi;

        template <Number TNumber>
        static inline constexpr TNumber Tau = Numeric<TNumber>::Tau;

        template <Number TNumber>
        static inline constexpr TNumber DegreesPerRadians = Numeric<TNumber>::DegreesPerRadians;

        template <Number TNumber>
        static inline constexpr TNumber RadiansPerDegrees = Numeric<TNumber>::RadiansPerDegrees;

        template <Number TNumber>
        static inline constexpr TNumber Negate(TNumber value)
        {
            if constexpr (SignedNumber<TNumber>)
                return -value;
            else
                return value;
        }

        template <Number TNumber>
        static inline constexpr TNumber Add(TNumber value1, TNumber value2)
        {
            return value1 + value2;
        }

        template <Number TNumber>
        static inline constexpr TNumber Subtract(TNumber value1, TNumber value2)
        {
            return value1 - value2;
        }

        template <Number TNumber>
        static inline constexpr TNumber Multiply(TNumber value1, TNumber value2)
        {
            return value1 * value2;
        }

        template <Number TNumber>
        static inline constexpr TNumber Divide(TNumber value1, TNumber value2)
        {
            return value1 / value2;
        }

        template <Number TNumber>
        static inline constexpr TNumber Modulo(TNumber value1, TNumber value2)
        {
            return value1 % value2;
        }

        template <Number TNumber>
        static inline constexpr TNumber Abs(TNumber value)
        {
            return (value < Zero<TNumber>) ? -value : value;
        }

        template <Number TNumber>
        static inline constexpr TNumber Min(TNumber value1, TNumber value2)
        {
            return (value1 < value2) ? value1 : value2;
        }

        template <Number TNumber>
        static inline constexpr TNumber Max(TNumber value1, TNumber value2)
        {
            return (value1 > value2) ? value1 : value2;
        }

        template <Number TNumber>
        static inline constexpr TNumber Clamp(TNumber value, TNumber min, TNumber max)
        {
            return Min(Max(value, min), max);
        }

        template <Number TNumber>
        static inline constexpr bool ApproximatelyEqual(TNumber value1, TNumber value2)
        {
            TNumber difference = Subtract(value1, value2);
            return Abs(difference) < Epsilon<TNumber>;
        }

        template <Number TNumber>
        static inline constexpr TNumber Lerp(TNumber source, TNumber target, TNumber time)
        {
            return (source * (One<TNumber> - time)) + (target * time);
        }

        template <Number TNumber>
        static inline constexpr TNumber Sqrt(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Sqrt(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Sqrt(value);
            else
                return Internal::Sqrt(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Pow(TNumber value, TNumber exponent)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Pow(value, exponent);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Pow(value, exponent);
            else
                return Internal::Pow(As<f32>(value), As<f32>(exponent));
        }

        template <Number TNumber>
        static inline constexpr TNumber Exp(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Exp(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Exp(value);
            else
                return Internal::Exp(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Log(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Log(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Log(value);
            else
                return Internal::Log(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Log(TNumber value, TNumber base)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Log(value, base);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Log(value, base);
            else
                return Internal::Log(As<f32>(value), As<f32>(base));
        }

        template <Number TNumber>
        static inline constexpr TNumber Log2(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Log2(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Log2(value);
            else
                return Internal::Log2(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Log10(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Log10(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Log10(value);
            else
                return Internal::Log10(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Sin(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Sin(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Sin(value);
            else
                return Internal::Sin(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Cos(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Cos(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Cos(value);
            else
                return Internal::Cos(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Tan(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Tan(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Tan(value);
            else
                return Internal::Tan(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Asin(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Asin(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Asin(value);
            else
                return Internal::Asin(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Acos(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Acos(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Acos(value);
            else
                return Internal::Acos(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Atan(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Atan(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Atan(value);
            else
                return Internal::Atan(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Atan2(TNumber y, TNumber x)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Atan2(y, x);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Atan2(y, x);
            else
                return Internal::Atan2(As<f32>(y), As<f32>(x));
        }

        template <Number TNumber>
        static inline constexpr TNumber Sinh(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Sinh(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Sinh(value);
            else
                return Internal::Sinh(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Cosh(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Cosh(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Cosh(value);
            else
                return Internal::Cosh(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Tanh(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Tanh(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Tanh(value);
            else
                return Internal::Tanh(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Asinh(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Asinh(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Asinh(value);
            else
                return Internal::Asinh(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Acosh(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Acosh(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Acosh(value);
            else
                return Internal::Acosh(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber Atanh(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Atanh(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Atanh(value);
            else
                return Internal::Atanh(As<f32>(value));
        }

        template <Number TNumber>
        static inline constexpr TNumber ToRadians(TNumber degrees)
        {
            return Multiply(degrees, RadiansPerDegrees<TNumber>);
        }

        template <Number TNumber>
        static inline constexpr TNumber ToDegrees(TNumber radians)
        {
            return Multiply(radians, DegreesPerRadians<TNumber>);
        }
    }
}

#endif