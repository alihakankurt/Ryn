#pragma once

#include <Ryn/Core/Traits.hpp>
#include <Ryn/Numerics/Math.hpp>

namespace Ryn
{
    template <Traits::Number TNumber>
    struct Vector2
    {
        TNumber X;
        TNumber Y;

        constexpr Vector2() :
            X{},
            Y{} {}

        constexpr Vector2(TNumber x, TNumber y) :
            X(x),
            Y(y) {}

        constexpr TNumber LengthSquared() const { return X * X + Y * Y; }
        constexpr TNumber Length() const { return Math::Sqrt(LengthSquared()); }

        constexpr Vector2 Normalize() const { return *this / Length(); }
        constexpr TNumber Dot(const Vector2& other) const { return X * other.X + Y * other.Y; }
        constexpr TNumber Cross(const Vector2& other) const { return X * other.Y - Y * other.X; }
        constexpr TNumber DistanceSquared(const Vector2& other) const { return (*this - other).LengthSquared(); }
        constexpr TNumber Distance(const Vector2& other) const { return (*this - other).Length(); }

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

        constexpr Vector2& operator*=(TNumber scalar)
        {
            X *= scalar;
            Y *= scalar;
            return *this;
        }

        constexpr Vector2& operator/=(TNumber scalar)
        {
            if constexpr (Traits::FloatingPoint<TNumber>)
                if (scalar == 0) return *this;

            X /= scalar;
            Y /= scalar;
            return *this;
        }

        constexpr Vector2 operator-() const { return Vector2{-X, -Y}; }
        constexpr Vector2 operator+(const Vector2& other) const { return Vector2{X + other.X, Y + other.Y}; }
        constexpr Vector2 operator-(const Vector2& other) const { return Vector2{X - other.X, Y - other.Y}; }
        constexpr Vector2 operator*(TNumber scalar) const { return Vector2{X * scalar, Y * scalar}; }
        constexpr Vector2 operator/(TNumber scalar) const { return Vector2{X / scalar, Y / scalar}; }

        constexpr bool operator==(const Vector2& other) const { return X == other.X && Y == other.Y; }
        constexpr bool operator!=(const Vector2& other) const { return !(*this == other); }

        static constexpr Vector2 Zero() { return Vector2{0, 0}; }
        static constexpr Vector2 One() { return Vector2{1, 1}; }
    };

    template <Traits::Number TNumber>
    constexpr Vector2<TNumber> operator*(TNumber scalar, const Vector2<TNumber>& vector)
    {
        return vector * scalar;
    }
}
