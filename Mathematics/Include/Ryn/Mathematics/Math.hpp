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
        template <Number TNumber>
        static inline constexpr TNumber Zero = As<TNumber>(0);

        template <Number TNumber>
        static inline constexpr TNumber One = As<TNumber>(1);

        template <Number TNumber>
        static inline constexpr TNumber Epsilon = As<TNumber>(0.00001);

        template <Number TNumber>
        static inline constexpr TNumber E = As<TNumber>(2.71828182845904523536);

        template <Number TNumber>
        static inline constexpr TNumber Pi = As<TNumber>(3.14159265358979323846);

        template <Number TNumber>
        static inline constexpr TNumber HalfPi = As<TNumber>(1.57079632679489661923);

        template <Number TNumber>
        static inline constexpr TNumber Tau = As<TNumber>(6.28318530717958647692);

        template <Number TNumber>
        static inline constexpr bool ApproximatelyEqual(TNumber value1, TNumber value2)
        {
            TNumber difference = Subtract(value1, value2);
            return Abs(difference) < Epsilon<TNumber>;
        }

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
    }
}

#endif