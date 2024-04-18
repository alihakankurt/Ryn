#ifndef __RYN_MATHEMATICS_VECTOR2_HPP__
#define __RYN_MATHEMATICS_VECTOR2_HPP__

#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <typename TScalar>
    requires IsNumber<TScalar>
    struct Vector2
    {
        TScalar X;
        TScalar Y;

        Vector2()
        {
            X = Math::Zero<TScalar>;
            Y = Math::Zero<TScalar>;
        }

        Vector2(TScalar x, TScalar y)
        {
            X = x;
            Y = y;
        }

        Vector2 operator-() const
        {
            if constexpr (!IsSignedNumber<TScalar>)
                return *this;

            TScalar x = Math::Negate(X);
            TScalar y = Math::Negate(Y);
            return Vector2{x, y};
        }

        Vector2 operator+(const Vector2& other) const
        {
            Vector2 result = *this;
            result += other;
            return result;
        }

        Vector2& operator+=(const Vector2& other)
        {
            X = Math::Add(X, other.X);
            Y = Math::Add(Y, other.Y);
            return *this;
        }

        Vector2 operator-(const Vector2& other) const
        {
            Vector2 result = *this;
            result -= other;
            return result;
        }

        Vector2& operator-=(const Vector2& other)
        {
            X = Math::Subtract(X, other.X);
            Y = Math::Subtract(Y, other.Y);
            return *this;
        }

        Vector2 operator*(TScalar scalar) const
        {
            Vector2 result = *this;
            result *= scalar;
            return result;
        }

        Vector2& operator*=(TScalar scalar)
        {
            X = Math::Multiply(X, scalar);
            Y = Math::Multiply(Y, scalar);
            return *this;
        }

        Vector2 operator/(TScalar scalar) const
        {
            Vector2 result = *this;
            result /= scalar;
            return result;
        }

        Vector2& operator/=(TScalar scalar)
        {
            if (Math::ApproximatelyEqual(scalar, Math::Zero<TScalar>))
                return *this;

            X = Math::Divide(X, scalar);
            Y = Math::Divide(Y, scalar);
            return *this;
        }

        bool operator==(const Vector2& other) const
        {
            return Math::ApproximatelyEqual(X, other.X)
                && Math::ApproximatelyEqual(Y, other.Y);
        }

        bool operator!=(const Vector2& other) const
        {
            return !(*this == other);
        }

        TScalar Dot(const Vector2& other) const
        {
            TScalar x = Math::Multiply(X, other.X);
            TScalar y = Math::Multiply(Y, other.Y);
            return Math::Add(x, y);
        }

        TScalar LengthSquared() const
        {
            return Dot(*this);
        }

        TScalar Length() const
        {
            return Math::Sqrt(LengthSquared());
        }

        Vector2 Normalize() const
        {
            TScalar length = Length();
            if (Math::ApproximatelyEqual(length, Math::Zero<TScalar>))
                return *this;

            return *this / length;
        }

        Vector2 Lerp(const Vector2& target, TScalar time) const
        {
            TScalar x = Math::Lerp(X, target.X, time);
            TScalar y = Math::Lerp(Y, target.Y, time);
            return Vector2{x, y};
        }
    };
}

#endif