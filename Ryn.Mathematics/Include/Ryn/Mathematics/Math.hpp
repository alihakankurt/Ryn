#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Traits.hpp>
#include <Ryn/Mathematics/Constants.hpp>

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
    template <Traits::Number TScalar>
    constexpr TScalar Add(TScalar value1, TScalar value2)
    {
        return value1 + value2;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Subtract(TScalar value1, TScalar value2)
    {
        return value1 - value2;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Multiply(TScalar value1, TScalar value2)
    {
        return value1 * value2;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Divide(TScalar value1, TScalar value2)
    {
        return value1 / value2;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Modulo(TScalar value1, TScalar value2)
    {
        return value1 % value2;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Negate(TScalar value)
    {
        if constexpr (Traits::SignedInteger<TScalar> || Traits::FloatingPoint<TScalar>)
            return -value;
        else
            return value;
    }

    template <Traits::Number TScalar>
    constexpr bool IsZero(TScalar value)
    {
        return value == MathConstants<TScalar>::Zero;
    }

    template <Traits::Number TScalar>
    constexpr bool IsNegative(TScalar value)
    {
        if constexpr (Traits::SignedInteger<TScalar> || Traits::FloatingPoint<TScalar>)
            return value < MathConstants<TScalar>::Zero;
        else
            return false;
    }

    template <Traits::Number TScalar>
    constexpr bool IsPositive(TScalar value)
    {
        return value > MathConstants<TScalar>::Zero;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Abs(TScalar value)
    {
        if constexpr (Traits::SignedInteger<TScalar> || Traits::FloatingPoint<TScalar>)
            return (value < MathConstants<TScalar>::Zero) ? -value : value;
        else
            return value;
    }

    template <Traits::Number TScalar>
    constexpr bool IsApproximatelyEqual(TScalar value1, TScalar value2, TScalar epsilon = MathConstants<TScalar>::Epsilon)
    {
        return Abs(value1 - value2) <= epsilon;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Min(TScalar value1, TScalar value2)
    {
        return (value1 < value2) ? value1 : value2;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Max(TScalar value1, TScalar value2)
    {
        return (value1 > value2) ? value1 : value2;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Clamp(TScalar value, TScalar min, TScalar max)
    {
        return Min(Max(value, min), max);
    }

    template <Traits::Number TScalar, Traits::Number TTime = f32>
    constexpr TScalar Lerp(TScalar value1, TScalar value2, TTime time)
    {
        return static_cast<TScalar>((MathConstants<TTime>::One - time) * value1 + time * value2);
    }

    template <Traits::Number TScalar>
    constexpr TScalar Floor(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return static_cast<TScalar>(Private::Math::FloorImpl(value));
        else
            return value;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Ceil(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return static_cast<TScalar>(Private::Math::CeilImpl(value));
        else
            return value;
    }

    template <Traits::Number TScalar>
    constexpr TScalar Sqrt(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::SqrtImpl(value);
        else
            return static_cast<TScalar>(Private::Math::SqrtImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Pow(TScalar base, TScalar exponent)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::PowImpl(base, exponent);
        else
            return static_cast<TScalar>(Private::Math::PowImpl(static_cast<f32>(base), static_cast<f32>(exponent)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Sin(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::SinImpl(value);
        else
            return static_cast<TScalar>(Private::Math::SinImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Cos(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::CosImpl(value);
        else
            return static_cast<TScalar>(Private::Math::CosImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Tan(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::TanImpl(value);
        else
            return static_cast<TScalar>(Private::Math::TanImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Asin(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::AsinImpl(value);
        else
            return static_cast<TScalar>(Private::Math::AsinImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Acos(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::AcosImpl(value);
        else
            return static_cast<TScalar>(Private::Math::AcosImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Atan(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::AtanImpl(value);
        else
            return static_cast<TScalar>(Private::Math::AtanImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Atan2(TScalar y, TScalar x)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::Atan2Impl(y, x);
        else
            return static_cast<TScalar>(Private::Math::Atan2Impl(static_cast<f32>(y), static_cast<f32>(x)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Sinh(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::SinhImpl(value);
        else
            return static_cast<TScalar>(Private::Math::SinhImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Cosh(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::CoshImpl(value);
        else
            return static_cast<TScalar>(Private::Math::CoshImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Tanh(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::TanhImpl(value);
        else
            return static_cast<TScalar>(Private::Math::TanhImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Asinh(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::AsinhImpl(value);
        else
            return static_cast<TScalar>(Private::Math::AsinhImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Acosh(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::AcoshImpl(value);
        else
            return static_cast<TScalar>(Private::Math::AcoshImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Atanh(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::AtanhImpl(value);
        else
            return static_cast<TScalar>(Private::Math::AtanhImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Log(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::LogImpl(value);
        else
            return static_cast<TScalar>(Private::Math::LogImpl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Log(TScalar value, TScalar base)
    {
        return Log(value) / Log(base);
    }

    template <Traits::Number TScalar>
    constexpr TScalar Log2(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::Log2Impl(value);
        else
            return static_cast<TScalar>(Private::Math::Log2Impl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Log10(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::Log10Impl(value);
        else
            return static_cast<TScalar>(Private::Math::Log10Impl(static_cast<f32>(value)));
    }

    template <Traits::Number TScalar>
    constexpr TScalar Exp(TScalar value)
    {
        if constexpr (Traits::FloatingPoint<TScalar>)
            return Private::Math::ExpImpl(value);
        else
            return static_cast<TScalar>(Private::Math::ExpImpl(static_cast<f32>(value)));
    }
}
