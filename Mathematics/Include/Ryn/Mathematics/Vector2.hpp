#ifndef __RYN_MATHEMATICS_VECTOR2_HPP__
#define __RYN_MATHEMATICS_VECTOR2_HPP__

#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <Number TNumber>
    struct Vector2
    {
        TNumber X;
        TNumber Y;

        Vector2()
        {
            X = Math::Zero<TNumber>;
            Y = Math::Zero<TNumber>;
        }

        Vector2(TNumber x, TNumber y)
        {
            X = x;
            Y = y;
        }

        Vector2 operator-() const
        {
            TNumber x = Math::Negate(X);
            TNumber y = Math::Negate(Y);
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

        Vector2 operator*(TNumber scalar) const
        {
            Vector2 result = *this;
            result *= scalar;
            return result;
        }

        Vector2& operator*=(TNumber scalar)
        {
            X = Math::Multiply(X, scalar);
            Y = Math::Multiply(Y, scalar);
            return *this;
        }

        Vector2 operator/(TNumber scalar) const
        {
            Vector2 result = *this;
            result /= scalar;
            return result;
        }

        Vector2& operator/=(TNumber scalar)
        {
            if (Math::ApproximatelyEqual(scalar, Math::Zero<TNumber>))
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

        TNumber Dot(const Vector2& other) const
        {
            TNumber x = Math::Multiply(X, other.X);
            TNumber y = Math::Multiply(Y, other.Y);
            return Math::Add(x, y);
        }

        TNumber LengthSquared() const
        {
            return Dot(*this);
        }

        TNumber Length() const
        {
            return Math::Sqrt(LengthSquared());
        }

        Vector2 Normalize() const
        {
            TNumber length = Length();
            if (Math::ApproximatelyEqual(length, Math::Zero<TNumber>))
                return *this;

            return *this / length;
        }

        Vector2 Lerp(const Vector2& target, TNumber time) const
        {
            TNumber x = Math::Lerp(X, target.X, time);
            TNumber y = Math::Lerp(Y, target.Y, time);
            return Vector2{x, y};
        }
    };
}

#endif