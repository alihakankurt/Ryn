#ifndef __RYN_MATHEMATICS_MATRIX4X4_HPP__
#define __RYN_MATHEMATICS_MATRIX4X4_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    template <Number TScalar>
    struct Matrix4x4
    {
        TScalar M11;
        TScalar M12;
        TScalar M13;
        TScalar M14;
        TScalar M21;
        TScalar M22;
        TScalar M23;
        TScalar M24;
        TScalar M31;
        TScalar M32;
        TScalar M33;
        TScalar M34;
        TScalar M41;
        TScalar M42;
        TScalar M43;
        TScalar M44;

        inline constexpr Matrix4x4(TScalar scalar = Math::One<TScalar>)
        {
            M11 = scalar;
            M22 = scalar;
            M33 = scalar;
            M44 = scalar;
        }

        inline constexpr Matrix4x4(const TScalar (&elements)[4][4])
        {
            M11 = elements[0][0];
            M12 = elements[0][1];
            M13 = elements[0][2];
            M14 = elements[0][3];

            M21 = elements[1][0];
            M22 = elements[1][1];
            M23 = elements[1][2];
            M24 = elements[1][3];

            M31 = elements[2][0];
            M32 = elements[2][1];
            M33 = elements[2][2];
            M34 = elements[2][3];

            M41 = elements[3][0];
            M42 = elements[3][1];
            M43 = elements[3][2];
            M44 = elements[3][3];
        }

        inline constexpr Matrix4x4 operator-() const
        {
            Matrix4x4 result;

            result.M11 = Math::Negate(M11);
            result.M12 = Math::Negate(M12);
            result.M13 = Math::Negate(M13);
            result.M14 = Math::Negate(M14);

            result.M21 = Math::Negate(M21);
            result.M22 = Math::Negate(M22);
            result.M23 = Math::Negate(M23);
            result.M24 = Math::Negate(M24);

            result.M31 = Math::Negate(M31);
            result.M32 = Math::Negate(M32);
            result.M33 = Math::Negate(M33);
            result.M34 = Math::Negate(M34);

            result.M41 = Math::Negate(M41);
            result.M42 = Math::Negate(M42);
            result.M43 = Math::Negate(M43);
            result.M44 = Math::Negate(M44);

            return result;
        }

        inline constexpr Matrix4x4 operator+(const Matrix4x4& other) const
        {
            Matrix4x4 result;

            result.M11 = Math::Add(M11, other.M11);
            result.M12 = Math::Add(M12, other.M12);
            result.M13 = Math::Add(M13, other.M13);
            result.M14 = Math::Add(M14, other.M14);

            result.M21 = Math::Add(M21, other.M21);
            result.M22 = Math::Add(M22, other.M22);
            result.M23 = Math::Add(M23, other.M23);
            result.M24 = Math::Add(M24, other.M24);

            result.M31 = Math::Add(M31, other.M31);
            result.M32 = Math::Add(M32, other.M32);
            result.M33 = Math::Add(M33, other.M33);
            result.M34 = Math::Add(M34, other.M34);

            result.M41 = Math::Add(M41, other.M41);
            result.M42 = Math::Add(M42, other.M42);
            result.M43 = Math::Add(M43, other.M43);
            result.M44 = Math::Add(M44, other.M44);

            return result;
        }

        inline constexpr Matrix4x4& operator+=(const Matrix4x4& other)
        {
            return *this = *this + other;
        }

        inline constexpr Matrix4x4 operator-(const Matrix4x4& other) const
        {
            Matrix4x4 result;

            result.M11 = Math::Subtract(M11, other.M11);
            result.M12 = Math::Subtract(M12, other.M12);
            result.M13 = Math::Subtract(M13, other.M13);
            result.M14 = Math::Subtract(M14, other.M14);

            result.M21 = Math::Subtract(M21, other.M21);
            result.M22 = Math::Subtract(M22, other.M22);
            result.M23 = Math::Subtract(M23, other.M23);
            result.M24 = Math::Subtract(M24, other.M24);

            result.M31 = Math::Subtract(M31, other.M31);
            result.M32 = Math::Subtract(M32, other.M32);
            result.M33 = Math::Subtract(M33, other.M33);
            result.M34 = Math::Subtract(M34, other.M34);

            result.M41 = Math::Subtract(M41, other.M41);
            result.M42 = Math::Subtract(M42, other.M42);
            result.M43 = Math::Subtract(M43, other.M43);
            result.M44 = Math::Subtract(M44, other.M44);

            return result;
        }

        inline constexpr Matrix4x4& operator-=(const Matrix4x4& other)
        {
            return *this = *this - other;
        }

        inline constexpr Matrix4x4 operator*(const Matrix4x4& other) const
        {
            Matrix4x4 result;

            result.M11 = Math::Add(Math::Add(Math::Multiply(M11, other.M11), Math::Multiply(M12, other.M21)), Math::Add(Math::Multiply(M13, other.M31), Math::Multiply(M14, other.M41)));
            result.M12 = Math::Add(Math::Add(Math::Multiply(M11, other.M12), Math::Multiply(M12, other.M22)), Math::Add(Math::Multiply(M13, other.M32), Math::Multiply(M14, other.M42)));
            result.M13 = Math::Add(Math::Add(Math::Multiply(M11, other.M13), Math::Multiply(M12, other.M23)), Math::Add(Math::Multiply(M13, other.M33), Math::Multiply(M14, other.M43)));
            result.M14 = Math::Add(Math::Add(Math::Multiply(M11, other.M14), Math::Multiply(M12, other.M24)), Math::Add(Math::Multiply(M13, other.M34), Math::Multiply(M14, other.M44)));

            result.M21 = Math::Add(Math::Add(Math::Multiply(M21, other.M11), Math::Multiply(M22, other.M21)), Math::Add(Math::Multiply(M23, other.M31), Math::Multiply(M24, other.M41)));
            result.M22 = Math::Add(Math::Add(Math::Multiply(M21, other.M12), Math::Multiply(M22, other.M22)), Math::Add(Math::Multiply(M23, other.M32), Math::Multiply(M24, other.M42)));
            result.M23 = Math::Add(Math::Add(Math::Multiply(M21, other.M13), Math::Multiply(M22, other.M23)), Math::Add(Math::Multiply(M23, other.M33), Math::Multiply(M24, other.M43)));
            result.M24 = Math::Add(Math::Add(Math::Multiply(M21, other.M14), Math::Multiply(M22, other.M24)), Math::Add(Math::Multiply(M23, other.M34), Math::Multiply(M24, other.M44)));

            result.M31 = Math::Add(Math::Add(Math::Multiply(M31, other.M11), Math::Multiply(M32, other.M21)), Math::Add(Math::Multiply(M33, other.M31), Math::Multiply(M34, other.M41)));
            result.M32 = Math::Add(Math::Add(Math::Multiply(M31, other.M12), Math::Multiply(M32, other.M22)), Math::Add(Math::Multiply(M33, other.M32), Math::Multiply(M34, other.M42)));
            result.M33 = Math::Add(Math::Add(Math::Multiply(M31, other.M13), Math::Multiply(M32, other.M23)), Math::Add(Math::Multiply(M33, other.M33), Math::Multiply(M34, other.M43)));
            result.M34 = Math::Add(Math::Add(Math::Multiply(M31, other.M14), Math::Multiply(M32, other.M24)), Math::Add(Math::Multiply(M33, other.M34), Math::Multiply(M34, other.M44)));

            result.M41 = Math::Add(Math::Add(Math::Multiply(M41, other.M11), Math::Multiply(M42, other.M21)), Math::Add(Math::Multiply(M43, other.M31), Math::Multiply(M44, other.M41)));
            result.M42 = Math::Add(Math::Add(Math::Multiply(M41, other.M12), Math::Multiply(M42, other.M22)), Math::Add(Math::Multiply(M43, other.M32), Math::Multiply(M44, other.M42)));
            result.M43 = Math::Add(Math::Add(Math::Multiply(M41, other.M13), Math::Multiply(M42, other.M23)), Math::Add(Math::Multiply(M43, other.M33), Math::Multiply(M44, other.M43)));
            result.M44 = Math::Add(Math::Add(Math::Multiply(M41, other.M14), Math::Multiply(M42, other.M24)), Math::Add(Math::Multiply(M43, other.M34), Math::Multiply(M44, other.M44)));

            return result;
        }

        inline constexpr Matrix4x4& operator*=(const Matrix4x4& other)
        {
            return *this = *this * other;
        }

        inline constexpr Matrix4x4 operator*(TScalar scalar) const
        {
            Matrix4x4 result;

            result.M11 = Math::Multiply(M11, scalar);
            result.M12 = Math::Multiply(M12, scalar);
            result.M13 = Math::Multiply(M13, scalar);
            result.M14 = Math::Multiply(M14, scalar);

            result.M21 = Math::Multiply(M21, scalar);
            result.M22 = Math::Multiply(M22, scalar);
            result.M23 = Math::Multiply(M23, scalar);
            result.M24 = Math::Multiply(M24, scalar);

            result.M31 = Math::Multiply(M31, scalar);
            result.M32 = Math::Multiply(M32, scalar);
            result.M33 = Math::Multiply(M33, scalar);
            result.M34 = Math::Multiply(M34, scalar);

            result.M41 = Math::Multiply(M41, scalar);
            result.M42 = Math::Multiply(M42, scalar);
            result.M43 = Math::Multiply(M43, scalar);
            result.M44 = Math::Multiply(M44, scalar);

            return result;
        }

        inline constexpr Matrix4x4& operator*=(TScalar scalar)
        {
            return *this = *this * scalar;
        }

        inline constexpr Matrix4x4 operator/(TScalar scalar) const
        {
            if (scalar == Math::Zero<TScalar>)
                return *this;

            Matrix4x4 result;

            result.M11 = Math::Divide(M11, scalar);
            result.M12 = Math::Divide(M12, scalar);
            result.M13 = Math::Divide(M13, scalar);
            result.M14 = Math::Divide(M14, scalar);

            result.M21 = Math::Divide(M21, scalar);
            result.M22 = Math::Divide(M22, scalar);
            result.M23 = Math::Divide(M23, scalar);
            result.M24 = Math::Divide(M24, scalar);

            result.M31 = Math::Divide(M31, scalar);
            result.M32 = Math::Divide(M32, scalar);
            result.M33 = Math::Divide(M33, scalar);
            result.M34 = Math::Divide(M34, scalar);

            result.M41 = Math::Divide(M41, scalar);
            result.M42 = Math::Divide(M42, scalar);
            result.M43 = Math::Divide(M43, scalar);
            result.M44 = Math::Divide(M44, scalar);

            return result;
        }

        inline constexpr Matrix4x4& operator/=(TScalar scalar)
        {
            return *this = *this / scalar;
        }

        inline constexpr bool operator==(const Matrix4x4& other) const
        {
            return Math::ApproximatelyEqual(M11, other.M11) && Math::ApproximatelyEqual(M12, other.M12) && Math::ApproximatelyEqual(M13, other.M13) && Math::ApproximatelyEqual(M14, other.M14)
                && Math::ApproximatelyEqual(M21, other.M21) && Math::ApproximatelyEqual(M22, other.M22) && Math::ApproximatelyEqual(M23, other.M23) && Math::ApproximatelyEqual(M24, other.M24)
                && Math::ApproximatelyEqual(M31, other.M31) && Math::ApproximatelyEqual(M32, other.M32) && Math::ApproximatelyEqual(M33, other.M33) && Math::ApproximatelyEqual(M34, other.M34)
                && Math::ApproximatelyEqual(M41, other.M41) && Math::ApproximatelyEqual(M42, other.M42) && Math::ApproximatelyEqual(M43, other.M43) && Math::ApproximatelyEqual(M44, other.M44);
        }

        inline constexpr bool operator!=(const Matrix4x4& other) const
        {
            return !(*this == other);
        }

        inline constexpr Matrix4x4 Transpose() const
        {
            Matrix4x4 result;

            result.M11 = M11;
            result.M12 = M21;
            result.M13 = M31;
            result.M14 = M41;

            result.M21 = M12;
            result.M22 = M22;
            result.M23 = M32;
            result.M24 = M42;

            result.M31 = M13;
            result.M32 = M23;
            result.M33 = M33;
            result.M34 = M43;

            result.M41 = M14;
            result.M42 = M24;
            result.M43 = M34;
            result.M44 = M44;

            return result;
        }

        inline constexpr TScalar Determinant() const
        {
            TScalar a = Math::Multiply(M33, M44) - Math::Multiply(M34, M43);
            TScalar b = Math::Multiply(M32, M44) - Math::Multiply(M34, M42);
            TScalar c = Math::Multiply(M32, M43) - Math::Multiply(M33, M42);
            TScalar d = Math::Multiply(M31, M44) - Math::Multiply(M34, M41);
            TScalar e = Math::Multiply(M31, M43) - Math::Multiply(M33, M41);
            TScalar f = Math::Multiply(M31, M42) - Math::Multiply(M32, M41);

            TScalar g = Math::Multiply(M22, a) - Math::Multiply(M23, b) + Math::Multiply(M24, c);
            TScalar h = Math::Multiply(M21, a) - Math::Multiply(M23, d) + Math::Multiply(M24, e);
            TScalar i = Math::Multiply(M21, b) - Math::Multiply(M22, d) + Math::Multiply(M24, f);
            TScalar j = Math::Multiply(M21, c) - Math::Multiply(M22, e) + Math::Multiply(M23, f);

            return Math::Multiply(M11, g) - Math::Multiply(M12, h) + Math::Multiply(M13, i) - Math::Multiply(M14, j);
        }
    };
}

#endif