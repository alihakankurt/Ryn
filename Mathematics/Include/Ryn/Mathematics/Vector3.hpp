#ifndef __RYN_MATHEMATICS_VECTOR3_HPP__
#define __RYN_MATHEMATICS_VECTOR3_HPP__

#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <typename TScalar>
    requires IsNumber<TScalar>
    struct Vector3
    {
        TScalar Elements[3];
        TScalar& X = Elements[0];
        TScalar& Y = Elements[1];
        TScalar& Z = Elements[2];

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

        Vector3(const Vector3& other)
        {
            X = other.X;
            Y = other.Y;
            Z = other.Z;
        }

        Vector3& operator=(const Vector3& other)
        {
            X = other.X;
            Y = other.Y;
            Z = other.Z;
            return *this;
        }

        Vector3(Vector3&& other)
        {
            X = other.X;
            Y = other.Y;
            Z = other.Z;
        }

        Vector3& operator=(Vector3&& other)
        {
            X = other.X;
            Y = other.Y;
            Z = other.Z;
            return *this;
        }

        TScalar& operator[](usize index)
        {
            return Elements[index];
        }

        Vector3 operator-() const
        requires IsSignedNumber<TScalar>
        {
            TScalar x = Math::Negate(X);
            TScalar y = Math::Negate(Y);
            TScalar z = Math::Negate(Z);
            return Vector3{x, y, z};
        }

        Vector3 operator+(const Vector3& other) const
        {
            TScalar x = Math::Add(X, other.X);
            TScalar y = Math::Add(Y, other.Y);
            TScalar z = Math::Add(Z, other.Z);
            return Vector3{x, y, z};
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
            TScalar x = Math::Subtract(X, other.X);
            TScalar y = Math::Subtract(Y, other.Y);
            TScalar z = Math::Subtract(Z, other.Z);
            return Vector3{x, y, z};
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
            TScalar x = Math::Multiply(X, scalar);
            TScalar y = Math::Multiply(Y, scalar);
            TScalar z = Math::Multiply(Z, scalar);
            return Vector3{x, y, z};
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
            if (scalar == Math::Zero<TScalar>)
                return *this;

            TScalar x = Math::Divide(X, scalar);
            TScalar y = Math::Divide(Y, scalar);
            TScalar z = Math::Divide(Z, scalar);
            return Vector3{x, y, z};
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
    };
}

#endif