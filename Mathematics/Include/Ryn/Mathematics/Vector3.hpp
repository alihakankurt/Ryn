#ifndef __RYN_MATHEMATICS_VECTOR3_HPP__
#define __RYN_MATHEMATICS_VECTOR3_HPP__

#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <Number TNumber>
    struct Vector3
    {
        TNumber X;
        TNumber Y;
        TNumber Z;

        Vector3()
        {
            X = Math::Zero<TNumber>;
            Y = Math::Zero<TNumber>;
            Z = Math::Zero<TNumber>;
        }

        Vector3(TNumber x, TNumber y, TNumber z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        Vector3 operator-() const
        {
            TNumber x = Math::Negate(X);
            TNumber y = Math::Negate(Y);
            TNumber z = Math::Negate(Z);
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

        Vector3 operator*(TNumber scalar) const
        {
            Vector3 result = *this;
            result *= scalar;
            return result;
        }

        Vector3& operator*=(TNumber scalar)
        {
            X = Math::Multiply(X, scalar);
            Y = Math::Multiply(Y, scalar);
            Z = Math::Multiply(Z, scalar);
            return *this;
        }

        Vector3 operator/(TNumber scalar) const
        {
            Vector3 result = *this;
            result /= scalar;
            return result;
        }

        Vector3& operator/=(TNumber scalar)
        {
            if (scalar == Math::Zero<TNumber>)
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

        TNumber Dot(const Vector3& other) const
        {
            TNumber x = Math::Multiply(X, other.X);
            TNumber y = Math::Multiply(Y, other.Y);
            TNumber z = Math::Multiply(Z, other.Z);
            return Math::Add(Math::Add(x, y), z);
        }

        Vector3 Cross(const Vector3& other) const
        {
            TNumber x = Math::Subtract(Math::Multiply(Y, other.Z), Math::Multiply(Z, other.Y));
            TNumber y = Math::Subtract(Math::Multiply(Z, other.X), Math::Multiply(X, other.Z));
            TNumber z = Math::Subtract(Math::Multiply(X, other.Y), Math::Multiply(Y, other.X));
            return Vector3{x, y, z};
        }

        TNumber LengthSquared() const
        {
            return Dot(*this);
        }

        TNumber Length() const
        {
            return Math::Sqrt(LengthSquared());
        }

        Vector3 Normalize() const
        {
            TNumber length = Length();
            if (Math::ApproximatelyEqual(length, Math::Zero<TNumber>))
                return *this;

            return *this / length;
        }

        Vector3 Lerp(const Vector3& target, TNumber time) const
        {
            TNumber x = Math::Lerp(X, target.X, time);
            TNumber y = Math::Lerp(Y, target.Y, time);
            TNumber z = Math::Lerp(Z, target.Z, time);
            return Vector3{x, y, z};
        }
    };
}

#endif