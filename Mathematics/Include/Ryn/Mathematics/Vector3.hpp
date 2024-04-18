#ifndef __RYN_MATHEMATICS_VECTOR3_HPP__
#define __RYN_MATHEMATICS_VECTOR3_HPP__

#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <typename TScalar>
    requires IsNumber<TScalar>
    struct Vector3
    {
        TScalar X;
        TScalar Y;
        TScalar Z;

        Vector3()
        {
            X = Math::Zero<TScalar>;
            Y = Math::Zero<TScalar>;
            Z = Math::Zero<TScalar>;
        }

        Vector3(TScalar x, TScalar y, TScalar z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        Vector3 operator-() const
        {
            if constexpr (!IsSignedNumber<TScalar>)
                return *this;

            TScalar x = Math::Negate(X);
            TScalar y = Math::Negate(Y);
            TScalar z = Math::Negate(Z);
            return Vector3{x, y, z};
        }

        Vector3 operator+(const Vector3& other) const
        {
            Vector3 result = *this;
            result += other;
            return result;
        }

        Vector3& operator+=(const Vector3& other)
        {
            X = Math::Add(X, other.X);
            Y = Math::Add(Y, other.Y);
            Z = Math::Add(Z, other.Z);
            return *this;
        }

        Vector3 operator-(const Vector3& other) const
        {
            Vector3 result = *this;
            result -= other;
            return result;
        }

        Vector3& operator-=(const Vector3& other)
        {
            X = Math::Subtract(X, other.X);
            Y = Math::Subtract(Y, other.Y);
            Z = Math::Subtract(Z, other.Z);
            return *this;
        }

        Vector3 operator*(TScalar scalar) const
        {
            Vector3 result = *this;
            result *= scalar;
            return result;
        }

        Vector3& operator*=(TScalar scalar)
        {
            X = Math::Multiply(X, scalar);
            Y = Math::Multiply(Y, scalar);
            Z = Math::Multiply(Z, scalar);
            return *this;
        }

        Vector3 operator/(TScalar scalar) const
        {
            Vector3 result = *this;
            result /= scalar;
            return result;
        }

        Vector3& operator/=(TScalar scalar)
        {
            if (scalar == Math::Zero<TScalar>)
                return *this;

            X = Math::Divide(X, scalar);
            Y = Math::Divide(Y, scalar);
            Z = Math::Divide(Z, scalar);
            return *this;
        }

        bool operator==(const Vector3& other) const
        {
            return Math::ApproximatelyEqual(X, other.X)
                && Math::ApproximatelyEqual(Y, other.Y)
                && Math::ApproximatelyEqual(Z, other.Z);
        }

        bool operator!=(const Vector3& other) const
        {
            return !(*this == other);
        }

        TScalar Dot(const Vector3& other) const
        {
            TScalar x = Math::Multiply(X, other.X);
            TScalar y = Math::Multiply(Y, other.Y);
            TScalar z = Math::Multiply(Z, other.Z);
            return Math::Add(Math::Add(x, y), z);
        }

        Vector3 Cross(const Vector3& other) const
        {
            TScalar x = Math::Subtract(Math::Multiply(Y, other.Z), Math::Multiply(Z, other.Y));
            TScalar y = Math::Subtract(Math::Multiply(Z, other.X), Math::Multiply(X, other.Z));
            TScalar z = Math::Subtract(Math::Multiply(X, other.Y), Math::Multiply(Y, other.X));
            return Vector3{x, y, z};
        }

        TScalar LengthSquared() const
        {
            return Dot(*this);
        }

        TScalar Length() const
        {
            return Math::Sqrt(LengthSquared());
        }

        Vector3 Normalize() const
        {
            TScalar length = Length();
            if (Math::ApproximatelyEqual(length, Math::Zero<TScalar>))
                return *this;

            return *this / length;
        }

        Vector3 Lerp(const Vector3& target, TScalar time) const
        {
            TScalar x = Math::Lerp(X, target.X, time);
            TScalar y = Math::Lerp(Y, target.Y, time);
            TScalar z = Math::Lerp(Z, target.Z, time);
            return Vector3{x, y, z};
        }
    };
}

#endif