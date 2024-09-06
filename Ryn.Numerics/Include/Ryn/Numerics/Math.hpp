#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Traits.hpp>
#include <Ryn/Numerics/Constants.hpp>

namespace Ryn::Private::Math
{
    f32 FloorImpl(f32 value);
    f64 FloorImpl(f64 value);
    f32 CeilImpl(f32 value);
    f64 CeilImpl(f64 value);
    f32 SqrtImpl(f32 value);
    f64 SqrtImpl(f64 value);
    f32 PowImpl(f32 base, f32 exponent);
    f64 PowImpl(f64 base, f64 exponent);
    f32 SinImpl(f32 value);
    f64 SinImpl(f64 value);
    f32 CosImpl(f32 value);
    f64 CosImpl(f64 value);
    f32 TanImpl(f32 value);
    f64 TanImpl(f64 value);
    f32 AsinImpl(f32 value);
    f64 AsinImpl(f64 value);
    f32 AcosImpl(f32 value);
    f64 AcosImpl(f64 value);
    f32 AtanImpl(f32 value);
    f64 AtanImpl(f64 value);
    f32 Atan2Impl(f32 y, f32 x);
    f64 Atan2Impl(f64 y, f64 x);
    f32 SinhImpl(f32 value);
    f64 SinhImpl(f64 value);
    f32 CoshImpl(f32 value);
    f64 CoshImpl(f64 value);
    f32 TanhImpl(f32 value);
    f64 TanhImpl(f64 value);
    f32 AsinhImpl(f32 value);
    f64 AsinhImpl(f64 value);
    f32 AcoshImpl(f32 value);
    f64 AcoshImpl(f64 value);
    f32 AtanhImpl(f32 value);
    f64 AtanhImpl(f64 value);
    f32 LogImpl(f32 value);
    f64 LogImpl(f64 value);
    f32 Log2Impl(f32 value);
    f64 Log2Impl(f64 value);
    f32 Log10Impl(f32 value);
    f64 Log10Impl(f64 value);
    f32 ExpImpl(f32 value);
    f64 ExpImpl(f64 value);
}

namespace Ryn::Math
{
    template <Traits::Number TNumber>
    constexpr TNumber Add(TNumber value1, TNumber value2)
    {
        return value1 + value2;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Subtract(TNumber value1, TNumber value2)
    {
        return value1 - value2;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Multiply(TNumber value1, TNumber value2)
    {
        return value1 * value2;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Divide(TNumber value1, TNumber value2)
    {
        return value1 / value2;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Modulo(TNumber value1, TNumber value2)
    {
        return value1 % value2;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Negate(TNumber value)
    {
        if constexpr (Traits::SignedInteger<TNumber> || Traits::FloatingPoint<TNumber>)
            return -value;
        else
            return value;
    }

    template <Traits::Number TNumber>
    constexpr bool IsZero(TNumber value)
    {
        return value == NumericConstans<TNumber>::Zero;
    }

    template <Traits::Number TNumber>
    constexpr bool IsNegative(TNumber value)
    {
        if constexpr (Traits::SignedInteger<TNumber> || Traits::FloatingPoint<TNumber>)
            return value < NumericConstans<TNumber>::Zero;
        else
            return false;
    }

    template <Traits::Number TNumber>
    constexpr bool IsPositive(TNumber value)
    {
        return value > NumericConstans<TNumber>::Zero;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Abs(TNumber value)
    {
        if constexpr (Traits::SignedInteger<TNumber> || Traits::FloatingPoint<TNumber>)
            return (value < NumericConstans<TNumber>::Zero) ? -value : value;
        else
            return value;
    }

    template <Traits::Number TNumber>
    constexpr bool IsApproximatelyEqual(TNumber value1, TNumber value2, TNumber epsilon = NumericConstans<TNumber>::Epsilon)
    {
        return Abs(value1 - value2) <= epsilon;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Min(TNumber value1, TNumber value2)
    {
        return (value1 < value2) ? value1 : value2;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Max(TNumber value1, TNumber value2)
    {
        return (value1 > value2) ? value1 : value2;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Clamp(TNumber value, TNumber min, TNumber max)
    {
        return Min(Max(value, min), max);
    }

    template <Traits::Number TNumber, Traits::Number TTime = f32>
    constexpr TNumber Lerp(TNumber value1, TNumber value2, TTime time)
    {
        return static_cast<TNumber>((NumericConstans<TTime>::One - time) * value1 + time * value2);
    }

    template <Traits::Number TNumber>
    constexpr TNumber Floor(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return static_cast<TNumber>(Private::Math::FloorImpl(value));
        else
            return value;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Ceil(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return static_cast<TNumber>(Private::Math::CeilImpl(value));
        else
            return value;
    }

    template <Traits::Number TNumber>
    constexpr TNumber Sqrt(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::SqrtImpl(value);
        else
            return static_cast<TNumber>(Private::Math::SqrtImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Pow(TNumber base, TNumber exponent)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::PowImpl(base, exponent);
        else
            return static_cast<TNumber>(Private::Math::PowImpl(static_cast<f32>(base), static_cast<f32>(exponent)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Sin(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::SinImpl(value);
        else
            return static_cast<TNumber>(Private::Math::SinImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Cos(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::CosImpl(value);
        else
            return static_cast<TNumber>(Private::Math::CosImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Tan(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::TanImpl(value);
        else
            return static_cast<TNumber>(Private::Math::TanImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Asin(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::AsinImpl(value);
        else
            return static_cast<TNumber>(Private::Math::AsinImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Acos(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::AcosImpl(value);
        else
            return static_cast<TNumber>(Private::Math::AcosImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Atan(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::AtanImpl(value);
        else
            return static_cast<TNumber>(Private::Math::AtanImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Atan2(TNumber y, TNumber x)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::Atan2Impl(y, x);
        else
            return static_cast<TNumber>(Private::Math::Atan2Impl(static_cast<f32>(y), static_cast<f32>(x)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Sinh(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::SinhImpl(value);
        else
            return static_cast<TNumber>(Private::Math::SinhImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Cosh(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::CoshImpl(value);
        else
            return static_cast<TNumber>(Private::Math::CoshImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Tanh(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::TanhImpl(value);
        else
            return static_cast<TNumber>(Private::Math::TanhImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Asinh(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::AsinhImpl(value);
        else
            return static_cast<TNumber>(Private::Math::AsinhImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Acosh(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::AcoshImpl(value);
        else
            return static_cast<TNumber>(Private::Math::AcoshImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Atanh(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::AtanhImpl(value);
        else
            return static_cast<TNumber>(Private::Math::AtanhImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Log(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::LogImpl(value);
        else
            return static_cast<TNumber>(Private::Math::LogImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Log(TNumber value, TNumber base)
    {
        return Log(value) / Log(base);
    }

    template <Traits::Number TNumber>
    constexpr TNumber Log2(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::Log2Impl(value);
        else
            return static_cast<TNumber>(Private::Math::Log2Impl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Log10(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::Log10Impl(value);
        else
            return static_cast<TNumber>(Private::Math::Log10Impl(static_cast<f32>(value)));
    }

    template <Traits::Number TNumber>
    constexpr TNumber Exp(TNumber value)
    {
        if constexpr (Traits::FloatingPoint<TNumber>)
            return Private::Math::ExpImpl(value);
        else
            return static_cast<TNumber>(Private::Math::ExpImpl(static_cast<f32>(value)));
    }
}
