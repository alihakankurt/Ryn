#pragma once

#include <Ryn/Core/Traits.hpp>
#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <Traits::Number TScalar>
    struct Vector2
    {
        TScalar X;
        TScalar Y;

        constexpr Vector2() :
            X{},
            Y{} {}

        constexpr Vector2(TScalar x, TScalar y) :
            X(x),
            Y(y) {}

        constexpr TScalar LengthSquared() const { return X * X + Y * Y; }
        constexpr TScalar Length() const { return Math::Sqrt(LengthSquared()); }

        constexpr Vector2 Normalize() const { return *this / Length(); }
        constexpr Vector2 Perpendicular() const { return Vector2{-Y, X}; }

        constexpr TScalar DistanceSquared(const Vector2& other) const { return (*this - other).LengthSquared(); }
        constexpr TScalar Distance(const Vector2& other) const { return (*this - other).Length(); }

        constexpr TScalar Dot(const Vector2& other) const { return X * other.X + Y * other.Y; }
        constexpr TScalar Cross(const Vector2& other) const { return X * other.Y - Y * other.X; }

        constexpr Vector2& operator+=(const Vector2& other)
        {
            X += other.X;
            Y += other.Y;
            return *this;
        }

        constexpr Vector2& operator-=(const Vector2& other)
        {
            X -= other.X;
            Y -= other.Y;
            return *this;
        }

        constexpr Vector2& operator*=(TScalar scalar)
        {
            X *= scalar;
            Y *= scalar;
            return *this;
        }

        constexpr Vector2& operator/=(TScalar scalar)
        {
            if (scalar != MathConstants<TScalar>::Zero)
            {
                X /= scalar;
                Y /= scalar;
            }
            return *this;
        }

        constexpr Vector2 operator-() const
        {
            static_assert(Traits::SignedInteger<TScalar> || Traits::FloatingPoint<TScalar>, "Negate(-) operator requires signed scalar type.");
            return Vector2{-X, -Y};
        }

        constexpr Vector2 operator+(const Vector2& other) const { return Vector2{X + other.X, Y + other.Y}; }
        constexpr Vector2 operator-(const Vector2& other) const { return Vector2{X - other.X, Y - other.Y}; }
        constexpr Vector2 operator*(TScalar scalar) const { return Vector2{X * scalar, Y * scalar}; }
        constexpr Vector2 operator/(TScalar scalar) const { return Vector2{X / scalar, Y / scalar}; }

        constexpr bool operator==(const Vector2& other) const { return X == other.X && Y == other.Y; }
        constexpr bool operator!=(const Vector2& other) const { return !(*this == other); }

        static constexpr Vector2 Zero() { return Vector2{MathConstants<TScalar>::Zero, MathConstants<TScalar>::Zero}; }
        static constexpr Vector2 One() { return Vector2{MathConstants<TScalar>::One, MathConstants<TScalar>::One}; }
    };

    template <Traits::Number TScalar>
    constexpr Vector2<TScalar> operator*(TScalar scalar, const Vector2<TScalar>& vector)
    {
        return vector * scalar;
    }
}
