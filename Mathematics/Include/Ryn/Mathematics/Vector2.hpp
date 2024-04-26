#ifndef __RYN_MATHEMATICS_VECTOR2_HPP__
#define __RYN_MATHEMATICS_VECTOR2_HPP__

#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <Number TScalar>
    struct Vector2
    {
        TScalar X;
        TScalar Y;

        inline constexpr Vector2()
        {
            X = Math::Zero<TScalar>;
            Y = Math::Zero<TScalar>;
        }

        inline constexpr Vector2(TScalar x, TScalar y)
        {
            X = x;
            Y = y;
        }

        inline constexpr Vector2 operator-() const
        {
            Vector2 result;

            result.X = Math::Negate(X);
            result.Y = Math::Negate(Y);

            return result;
        }

        inline constexpr Vector2 operator+(const Vector2& other) const
        {
            Vector2 result;

            result.X = Math::Add(X, other.X);
            result.Y = Math::Add(Y, other.Y);

            return result;
        }

        inline constexpr Vector2& operator+=(const Vector2& other)
        {
            return *this = *this + other;
        }

        inline constexpr Vector2 operator-(const Vector2& other) const
        {
            Vector2 result;

            result.X = Math::Subtract(X, other.X);
            result.Y = Math::Subtract(Y, other.Y);

            return result;
        }

        inline constexpr Vector2& operator-=(const Vector2& other)
        {
            return *this = *this - other;
        }

        inline constexpr Vector2 operator*(TScalar scalar) const
        {
            Vector2 result;

            result.X = Math::Multiply(X, scalar);
            result.Y = Math::Multiply(Y, scalar);

            return result;
        }

        inline constexpr Vector2& operator*=(TScalar scalar)
        {
            return *this = *this * scalar;
        }

        inline constexpr Vector2 operator/(TScalar scalar) const
        {
            if (scalar == Math::Zero<TScalar>)
                return *this;

            Vector2 result;

            result.X = Math::Divide(X, scalar);
            result.Y = Math::Divide(Y, scalar);

            return result;
        }

        inline constexpr Vector2& operator/=(TScalar scalar)
        {
            return *this = *this / scalar;
        }

        inline constexpr bool operator==(const Vector2& other) const
        {
            return Math::ApproximatelyEqual(X, other.X)
                && Math::ApproximatelyEqual(Y, other.Y);
        }

        inline constexpr bool operator!=(const Vector2& other) const
        {
            return !(*this == other);
        }

        inline constexpr TScalar Dot(const Vector2& other) const
        {
            TScalar x = Math::Multiply(X, other.X);
            TScalar y = Math::Multiply(Y, other.Y);
            return Math::Add(x, y);
        }

        inline constexpr TScalar LengthSquared() const
        {
            return Dot(*this);
        }

        inline constexpr TScalar Length() const
        {
            return Math::Sqrt(LengthSquared());
        }

        inline constexpr Vector2 Normalize() const
        {
            TScalar length = Length();
            if (length == Math::Zero<TScalar>)
                return *this;

            return *this / length;
        }

        inline constexpr Vector2 Lerp(const Vector2& target, TScalar time) const
        {
            Vector2 result;

            result.X = Math::Lerp(X, target.X, time);
            result.Y = Math::Lerp(Y, target.Y, time);

            return result;
        }
    };
}

#endif