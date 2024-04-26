#ifndef __RYN_MATHEMATICS_VECTOR4_HPP__
#define __RYN_MATHEMATICS_VECTOR4_HPP__

#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <Number TScalar>
    struct Vector4
    {
        TScalar X;
        TScalar Y;
        TScalar Z;
        TScalar W;

        inline constexpr Vector4()
        {
            X = Math::Zero<TScalar>;
            Y = Math::Zero<TScalar>;
            Z = Math::Zero<TScalar>;
            W = Math::Zero<TScalar>;
        }

        inline constexpr Vector4(TScalar x, TScalar y, TScalar z, TScalar w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }

        inline constexpr Vector4 operator-() const
        {
            Vector4 result;

            result.X = Math::Negate(X);
            result.Y = Math::Negate(Y);
            result.Z = Math::Negate(Z);
            result.W = Math::Negate(W);

            return result;
        }

        inline constexpr Vector4 operator+(const Vector4& other) const
        {
            Vector4 result;

            result.X = Math::Add(X, other.X);
            result.Y = Math::Add(Y, other.Y);
            result.Z = Math::Add(Z, other.Z);
            result.W = Math::Add(W, other.W);

            return result;
        }

        inline constexpr Vector4& operator+=(const Vector4& other)
        {
            return *this = *this + other;
        }

        inline constexpr Vector4 operator-(const Vector4& other) const
        {
            Vector4 result;

            result.X = Math::Subtract(X, other.X);
            result.Y = Math::Subtract(Y, other.Y);
            result.Z = Math::Subtract(Z, other.Z);
            result.W = Math::Subtract(W, other.W);

            return result;
        }

        inline constexpr Vector4& operator-=(const Vector4& other)
        {
            return *this = *this - other;
        }

        inline constexpr Vector4 operator*(TScalar scalar) const
        {
            Vector4 result;

            result.X = Math::Multiply(X, scalar);
            result.Y = Math::Multiply(Y, scalar);
            result.Z = Math::Multiply(Z, scalar);
            result.W = Math::Multiply(W, scalar);

            return result;
        }

        inline constexpr Vector4& operator*=(TScalar scalar)
        {
            return *this = *this * scalar;
        }

        inline constexpr Vector4 operator/(TScalar scalar) const
        {
            if (scalar == Math::Zero<TScalar>)
                return *this;

            Vector4 result;

            result.X = Math::Divide(X, scalar);
            result.Y = Math::Divide(Y, scalar);
            result.Z = Math::Divide(Z, scalar);
            result.W = Math::Divide(W, scalar);

            return result;
        }

        inline constexpr Vector4& operator/=(TScalar scalar)
        {
            return *this = *this / scalar;
        }

        inline constexpr bool operator==(const Vector4& other) const
        {
            return Math::ApproximatelyEqual(X, other.X)
                && Math::ApproximatelyEqual(Y, other.Y)
                && Math::ApproximatelyEqual(Z, other.Z)
                && Math::ApproximatelyEqual(W, other.W);
        }

        inline constexpr bool operator!=(const Vector4& other) const
        {
            return !(*this == other);
        }

        inline constexpr TScalar Dot(const Vector4& other) const
        {
            TScalar x = Math::Multiply(X, other.X);
            TScalar y = Math::Multiply(Y, other.Y);
            TScalar z = Math::Multiply(Z, other.Z);
            TScalar w = Math::Multiply(W, other.W);
            return Math::Add(Math::Add(x, y), Math::Add(z, w));
        }

        inline constexpr TScalar LengthSquared() const
        {
            return Dot(*this);
        }

        inline constexpr TScalar Length() const
        {
            return Math::Sqrt(LengthSquared());
        }

        inline constexpr Vector4 Normalize() const
        {
            TScalar length = Length();
            if (length == Math::Zero<TScalar>)
                return *this;

            return *this / length;
        }

        inline constexpr Vector4 Lerp(const Vector4& target, TScalar time) const
        {
            Vector4 result;

            result.X = Math::Lerp(X, target.X, time);
            result.Y = Math::Lerp(Y, target.Y, time);
            result.Z = Math::Lerp(Z, target.Z, time);
            result.W = Math::Lerp(W, target.W, time);

            return result;
        }
    };
}

#endif