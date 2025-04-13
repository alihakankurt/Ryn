#pragma once

#include <Ryn/Core/Traits.hpp>
#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <Traits::Number TScalar>
    struct Vector3
    {
        TScalar X;
        TScalar Y;
        TScalar Z;

        constexpr Vector3() :
            X{},
            Y{},
            Z{} {}

        constexpr Vector3(TScalar x, TScalar y, TScalar z) :
            X(x),
            Y(y),
            Z(z) {}

        constexpr TScalar LengthSquared() const { return X * X + Y * Y + Z * Z; }
        constexpr TScalar Length() const { return Math::Sqrt(LengthSquared()); }

        constexpr Vector3 Normalize() const { return *this / Length(); }
        constexpr Vector3 Perpendicular() const { return Vector3{-Y, X, Z}; }

        constexpr TScalar DistanceSquared(const Vector3& other) const { return (*this - other).LengthSquared(); }
        constexpr TScalar Distance(const Vector3& other) const { return (*this - other).Length(); }

        constexpr TScalar Dot(const Vector3& other) const { return X * other.X + Y * other.Y + Z * other.Z; }
        constexpr Vector3 Cross(const Vector3& other) const
        {
            TScalar x = Y * other.Z - Z * other.Y;
            TScalar y = Z * other.X - X * other.Z;
            TScalar z = X * other.Y - Y * other.X;
            return Vector3{x, y, z};
        }

        constexpr Vector3& operator+=(const Vector3& other)
        {
            X += other.X;
            Y += other.Y;
            Z += other.Z;
            return *this;
        }

        constexpr Vector3& operator-=(const Vector3& other)
        {
            X -= other.X;
            Y -= other.Y;
            Z -= other.Z;
            return *this;
        }

        constexpr Vector3& operator*=(TScalar scalar)
        {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
            return *this;
        }

        constexpr Vector3& operator/=(TScalar scalar)
        {
            if (scalar != MathConstants<TScalar>::Zero)
            {
                X /= scalar;
                Y /= scalar;
                Z /= scalar;
            }
            return *this;
        }

        constexpr Vector3 operator-() const
        {
            static_assert(Traits::SignedInteger<TScalar> || Traits::FloatingPoint<TScalar>, "Negate(-) operator requires signed scalar type.");
            return Vector3{-X, -Y, -Z};
        }

        constexpr Vector3 operator+(const Vector3& other) const { return Vector3{X + other.X, Y + other.Y, Z + other.Z}; }
        constexpr Vector3 operator-(const Vector3& other) const { return Vector3{X - other.X, Y - other.Y, Z - other.Z}; }
        constexpr Vector3 operator*(TScalar scalar) const { return Vector3{X * scalar, Y * scalar, Z * scalar}; }
        constexpr Vector3 operator/(TScalar scalar) const { return Vector3{X / scalar, Y / scalar, Z / scalar}; }

        constexpr bool operator==(const Vector3& other) const { return X == other.X && Y == other.Y && Z == other.Z; }
        constexpr bool operator!=(const Vector3& other) const { return !(*this == other); }

        static constexpr Vector3 Zero() { return Vector3{MathConstants<TScalar>::Zero, MathConstants<TScalar>::Zero, MathConstants<TScalar>::Zero}; }
        static constexpr Vector3 One() { return Vector3{MathConstants<TScalar>::One, MathConstants<TScalar>::One, MathConstants<TScalar>::One}; }
    };

    template <Traits::Number TScalar>
    constexpr Vector3<TScalar> operator*(TScalar scalar, const Vector3<TScalar>& vector)
    {
        return vector * scalar;
    }
}
