#ifndef __RYN_MATHEMATICS_MATH_HPP__
#define __RYN_MATHEMATICS_MATH_HPP__

#include <Ryn/Core.hpp>

namespace Ryn::Math::Internal
{
    f32 Sqrt(f32 value) noexcept;
    f64 Sqrt(f64 value) noexcept;
}

namespace Ryn
{
    namespace Math
    {
        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Zero = As<TNumber>(0);

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber One = As<TNumber>(1);

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Epsilon = As<TNumber>(0.00001);

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber E = As<TNumber>(2.71828182845904523536);

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Pi = As<TNumber>(3.14159265358979323846);

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber HalfPi = As<TNumber>(1.57079632679489661923);

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Tau = As<TNumber>(6.28318530717958647692);

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline bool ApproximatelyEqual(TNumber value1, TNumber value2)
        {
            TNumber difference = Subtract(value1, value2);
            return Abs(difference) < Epsilon<TNumber>;
        }

        template <typename TNumber>
        requires IsSignedNumber<TNumber>
        static constexpr inline TNumber Negate(TNumber value)
        {
            return -value;
        }

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Add(TNumber value1, TNumber value2)
        {
            return value1 + value2;
        }

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Subtract(TNumber value1, TNumber value2)
        {
            return value1 - value2;
        }

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Multiply(TNumber value1, TNumber value2)
        {
            return value1 * value2;
        }

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Divide(TNumber value1, TNumber value2)
        {
            return value1 / value2;
        }

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Modulo(TNumber value1, TNumber value2)
        {
            return value1 % value2;
        }

        template <typename TNumber>
        requires IsSignedNumber<TNumber>
        static constexpr inline TNumber Abs(TNumber value)
        {
            return (value < Zero<TNumber>) ? -value : value;
        }

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Min(TNumber value1, TNumber value2)
        {
            return (value1 < value2) ? value1 : value2;
        }

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Max(TNumber value1, TNumber value2)
        {
            return (value1 > value2) ? value1 : value2;
        }

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Clamp(TNumber value, TNumber min, TNumber max)
        {
            return Min(Max(value, min), max);
        }

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Lerp(TNumber source, TNumber target, TNumber time)
        {
            return (source * (One<TNumber> - time)) + (target * time);
        }

        template <typename TNumber>
        requires IsNumber<TNumber>
        static constexpr inline TNumber Sqrt(TNumber value)
        {
            if constexpr (Is<TNumber, f64>)
                return Internal::Sqrt(value);
            else if constexpr (Is<TNumber, f32>)
                return Internal::Sqrt(value);
            else
                return Internal::Sqrt(As<f32>(value));
        }
    }
}

#endif