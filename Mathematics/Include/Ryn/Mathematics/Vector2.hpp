#ifndef __RYN_MATHEMATICS_VECTOR2_HPP__
#define __RYN_MATHEMATICS_VECTOR2_HPP__

#include <Ryn/Mathematics/Math.hpp>

namespace Ryn
{
    template <typename TScalar>
    requires IsNumber<TScalar>
    struct Vector2
    {
        TScalar Elements[2];
        TScalar& X = Elements[0];
        TScalar& Y = Elements[1];

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

        Vector2(const Vector2& other)
        {
            X = other.X;
            Y = other.Y;
        }

        Vector2& operator=(const Vector2& other)
        {
            X = other.X;
            Y = other.Y;
            return *this;
        }

        Vector2(Vector2&& other)
        {
            X = other.X;
            Y = other.Y;
        }

        Vector2& operator=(Vector2&& other)
        {
            X = other.X;
            Y = other.Y;
            return *this;
        }

        TScalar& operator[](usize index)
        {
            return Elements[index];
        }

        Vector2 operator-() const
        requires IsSignedNumber<TScalar>
        {
            TScalar x = Math::Negate(X);
            TScalar y = Math::Negate(Y);
            return Vector2{x, y};
        }

        Vector2 operator+(const Vector2& other) const
        {
            TScalar x = Math::Add(X, other.X);
            TScalar y = Math::Add(Y, other.Y);
            return Vector2{x, y};
        }

        Vector2& operator+=(const Vector2& other)
        {
            X = Math::Add(X, other.X);
            Y = Math::Add(Y, other.Y);
            return *this;
        }

        Vector2 operator-(const Vector2& other) const
        {
            TScalar x = Math::Subtract(X, other.X);
            TScalar y = Math::Subtract(Y, other.Y);
            return Vector2{x, y};
        }

        Vector2& operator-=(const Vector2& other)
        {
            X = Math::Subtract(X, other.X);
            Y = Math::Subtract(Y, other.Y);
            return *this;
        }

        Vector2 operator*(TScalar scalar) const
        {
            TScalar x = Math::Multiply(X, scalar);
            TScalar y = Math::Multiply(Y, scalar);
            return Vector2{x, y};
        }

        Vector2& operator*=(TScalar scalar)
        {
            X = Math::Multiply(X, scalar);
            Y = Math::Multiply(Y, scalar);
            return *this;
        }

        Vector2 operator/(TScalar scalar) const
        {
            if (scalar == Math::Zero<TScalar>)
                return *this;

            TScalar x = Math::Divide(X, scalar);
            TScalar y = Math::Divide(Y, scalar);
            return Vector2{x, y};
        }

        Vector2& operator/=(TScalar scalar)
        {
            if (scalar == Math::Zero<TScalar>)
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
    };
}

#endif