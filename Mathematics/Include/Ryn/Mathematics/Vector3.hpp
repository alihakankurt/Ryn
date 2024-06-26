#ifndef __RYN_MATHEMATICS_VECTOR3_HPP__
#define __RYN_MATHEMATICS_VECTOR3_HPP__

#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <Number TScalar>
    struct Vector3
    {
        TScalar X;
        TScalar Y;
        TScalar Z;

        inline constexpr Vector3()
        {
            X = Math::Zero<TScalar>;
            Y = Math::Zero<TScalar>;
            Z = Math::Zero<TScalar>;
        }

        inline constexpr Vector3(TScalar x, TScalar y, TScalar z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        inline constexpr Vector3 operator-() const
        {
            Vector3 result;

            result.X = Math::Negate(X);
            result.Y = Math::Negate(Y);
            result.Z = Math::Negate(Z);

            return result;
        }

        inline constexpr Vector3 operator+(const Vector3& other) const
        {
            Vector3 result;

            result.X = Math::Add(X, other.X);
            result.Y = Math::Add(Y, other.Y);
            result.Z = Math::Add(Z, other.Z);

            return result;
        }

        inline constexpr Vector3& operator+=(const Vector3& other)
        {
            return *this = *this + other;
        }

        inline constexpr Vector3 operator-(const Vector3& other) const
        {
            Vector3 result;

            result.X = Math::Subtract(X, other.X);
            result.Y = Math::Subtract(Y, other.Y);
            result.Z = Math::Subtract(Z, other.Z);

            return result;
        }

        inline constexpr Vector3& operator-=(const Vector3& other)
        {
            return *this = *this - other;
        }

        inline constexpr Vector3 operator*(TScalar scalar) const
        {
            Vector3 result;

            result.X = Math::Multiply(X, scalar);
            result.Y = Math::Multiply(Y, scalar);
            result.Z = Math::Multiply(Z, scalar);

            return result;
        }

        inline constexpr Vector3& operator*=(TScalar scalar)
        {
            return *this = *this * scalar;
        }

        inline constexpr Vector3 operator/(TScalar scalar) const
        {
            if (scalar == Math::Zero<TScalar>)
                return *this;

            Vector3 result;

            result.X = Math::Divide(X, scalar);
            result.Y = Math::Divide(Y, scalar);
            result.Z = Math::Divide(Z, scalar);

            return result;
        }

        inline constexpr Vector3& operator/=(TScalar scalar)
        {
            return *this = *this / scalar;
        }

        inline constexpr bool operator==(const Vector3& other) const
        {
            return Math::ApproximatelyEqual(X, other.X)
                && Math::ApproximatelyEqual(Y, other.Y)
                && Math::ApproximatelyEqual(Z, other.Z);
        }

        inline constexpr bool operator!=(const Vector3& other) const
        {
            return !(*this == other);
        }

        inline constexpr TScalar Dot(const Vector3& other) const
        {
            TScalar x = Math::Multiply(X, other.X);
            TScalar y = Math::Multiply(Y, other.Y);
            TScalar z = Math::Multiply(Z, other.Z);
            return Math::Add(Math::Add(x, y), z);
        }

        inline constexpr Vector3 Cross(const Vector3& other) const
        {
            TScalar x = Math::Subtract(Math::Multiply(Y, other.Z), Math::Multiply(Z, other.Y));
            TScalar y = Math::Subtract(Math::Multiply(Z, other.X), Math::Multiply(X, other.Z));
            TScalar z = Math::Subtract(Math::Multiply(X, other.Y), Math::Multiply(Y, other.X));
            return Vector3{x, y, z};
        }

        inline constexpr TScalar LengthSquared() const
        {
            return Dot(*this);
        }

        inline constexpr TScalar Length() const
        {
            return Math::Sqrt(LengthSquared());
        }

        inline constexpr Vector3 Normalize() const
        {
            TScalar length = Length();
            if (length == Math::Zero<TScalar>)
                return *this;

            return *this / length;
        }

        inline constexpr Vector3 Lerp(const Vector3& target, TScalar time) const
        {
            Vector3 result;

            result.X = Math::Lerp(X, target.X, time);
            result.Y = Math::Lerp(Y, target.Y, time);
            result.Z = Math::Lerp(Z, target.Z, time);

            return result;
        }
    };
}

#endif