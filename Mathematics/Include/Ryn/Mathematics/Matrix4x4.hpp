#ifndef __RYN_MATHEMATICS_MATRIX4X4_HPP__
#define __RYN_MATHEMATICS_MATRIX4X4_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    template <typename TScalar>
    requires IsNumber<TScalar>
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

        Matrix4x4()
        {
            M11 = 1;
            M22 = 1;
            M33 = 1;
            M44 = 1;
        }

        Matrix4x4(const TScalar (&elements)[4][4])
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

        Matrix4x4 operator-() const
        {
            if constexpr (!IsSignedNumber<TScalar>)
                return *this;

            Matrix4x4 result = *this;
            result *= Math::Negate(Math::One<TScalar>);
            return result;
        }

        Matrix4x4 operator+(const Matrix4x4& other) const
        {
            Matrix4x4 result = *this;
            result += other;
            return result;
        }

        Matrix4x4& operator+=(const Matrix4x4& other)
        {
            M11 = Math::Add(M11, other.M11);
            M12 = Math::Add(M12, other.M12);
            M13 = Math::Add(M13, other.M13);
            M14 = Math::Add(M14, other.M14);

            M21 = Math::Add(M21, other.M21);
            M22 = Math::Add(M22, other.M22);
            M23 = Math::Add(M23, other.M23);
            M24 = Math::Add(M24, other.M24);

            M31 = Math::Add(M31, other.M31);
            M32 = Math::Add(M32, other.M32);
            M33 = Math::Add(M33, other.M33);
            M34 = Math::Add(M34, other.M34);

            M41 = Math::Add(M41, other.M41);
            M42 = Math::Add(M42, other.M42);
            M43 = Math::Add(M43, other.M43);
            M44 = Math::Add(M44, other.M44);

            return *this;
        }

        Matrix4x4 operator-(const Matrix4x4& other) const
        {
            Matrix4x4 result = *this;
            result -= other;
            return result;
        }

        Matrix4x4& operator-=(const Matrix4x4& other)
        {
            M11 = Math::Subtract(M11, other.M11);
            M12 = Math::Subtract(M12, other.M12);
            M13 = Math::Subtract(M13, other.M13);
            M14 = Math::Subtract(M14, other.M14);

            M21 = Math::Subtract(M21, other.M21);
            M22 = Math::Subtract(M22, other.M22);
            M23 = Math::Subtract(M23, other.M23);
            M24 = Math::Subtract(M24, other.M24);

            M31 = Math::Subtract(M31, other.M31);
            M32 = Math::Subtract(M32, other.M32);
            M33 = Math::Subtract(M33, other.M33);
            M34 = Math::Subtract(M34, other.M34);

            M41 = Math::Subtract(M41, other.M41);
            M42 = Math::Subtract(M42, other.M42);
            M43 = Math::Subtract(M43, other.M43);
            M44 = Math::Subtract(M44, other.M44);

            return *this;
        }

        Matrix4x4 operator*(const Matrix4x4& other) const
        {
            Matrix4x4 result = *this;
            result *= other;
            return result;
        }

        Matrix4x4& operator*=(const Matrix4x4& other)
        {
            Matrix4x4 self = *this;

            M11 = Math::Add(Math::Add(Math::Multiply(self.M11, other.M11), Math::Multiply(self.M12, other.M21)), Math::Add(Math::Multiply(self.M13, other.M31), Math::Multiply(self.M14, other.M41)));
            M12 = Math::Add(Math::Add(Math::Multiply(self.M11, other.M12), Math::Multiply(self.M12, other.M22)), Math::Add(Math::Multiply(self.M13, other.M32), Math::Multiply(self.M14, other.M42)));
            M13 = Math::Add(Math::Add(Math::Multiply(self.M11, other.M13), Math::Multiply(self.M12, other.M23)), Math::Add(Math::Multiply(self.M13, other.M33), Math::Multiply(self.M14, other.M43)));
            M14 = Math::Add(Math::Add(Math::Multiply(self.M11, other.M14), Math::Multiply(self.M12, other.M24)), Math::Add(Math::Multiply(self.M13, other.M34), Math::Multiply(self.M14, other.M44)));

            M21 = Math::Add(Math::Add(Math::Multiply(self.M21, other.M11), Math::Multiply(self.M22, other.M21)), Math::Add(Math::Multiply(self.M23, other.M31), Math::Multiply(self.M24, other.M41)));
            M22 = Math::Add(Math::Add(Math::Multiply(self.M21, other.M12), Math::Multiply(self.M22, other.M22)), Math::Add(Math::Multiply(self.M23, other.M32), Math::Multiply(self.M24, other.M42)));
            M23 = Math::Add(Math::Add(Math::Multiply(self.M21, other.M13), Math::Multiply(self.M22, other.M23)), Math::Add(Math::Multiply(self.M23, other.M33), Math::Multiply(self.M24, other.M43)));
            M24 = Math::Add(Math::Add(Math::Multiply(self.M21, other.M14), Math::Multiply(self.M22, other.M24)), Math::Add(Math::Multiply(self.M23, other.M34), Math::Multiply(self.M24, other.M44)));

            M31 = Math::Add(Math::Add(Math::Multiply(self.M31, other.M11), Math::Multiply(self.M32, other.M21)), Math::Add(Math::Multiply(self.M33, other.M31), Math::Multiply(self.M34, other.M41)));
            M32 = Math::Add(Math::Add(Math::Multiply(self.M31, other.M12), Math::Multiply(self.M32, other.M22)), Math::Add(Math::Multiply(self.M33, other.M32), Math::Multiply(self.M34, other.M42)));
            M33 = Math::Add(Math::Add(Math::Multiply(self.M31, other.M13), Math::Multiply(self.M32, other.M23)), Math::Add(Math::Multiply(self.M33, other.M33), Math::Multiply(self.M34, other.M43)));
            M34 = Math::Add(Math::Add(Math::Multiply(self.M31, other.M14), Math::Multiply(self.M32, other.M24)), Math::Add(Math::Multiply(self.M33, other.M34), Math::Multiply(self.M34, other.M44)));

            M41 = Math::Add(Math::Add(Math::Multiply(self.M41, other.M11), Math::Multiply(self.M42, other.M21)), Math::Add(Math::Multiply(self.M43, other.M31), Math::Multiply(self.M44, other.M41)));
            M42 = Math::Add(Math::Add(Math::Multiply(self.M41, other.M12), Math::Multiply(self.M42, other.M22)), Math::Add(Math::Multiply(self.M43, other.M32), Math::Multiply(self.M44, other.M42)));
            M43 = Math::Add(Math::Add(Math::Multiply(self.M41, other.M13), Math::Multiply(self.M42, other.M23)), Math::Add(Math::Multiply(self.M43, other.M33), Math::Multiply(self.M44, other.M43)));
            M44 = Math::Add(Math::Add(Math::Multiply(self.M41, other.M14), Math::Multiply(self.M42, other.M24)), Math::Add(Math::Multiply(self.M43, other.M34), Math::Multiply(self.M44, other.M44)));

            return *this;
        }

        Matrix4x4 operator*(TScalar scalar) const
        {
            Matrix4x4 result = *this;
            result *= scalar;
            return result;
        }

        Matrix4x4& operator*=(TScalar scalar)
        {
            M11 = Math::Multiply(M11, scalar);
            M12 = Math::Multiply(M12, scalar);
            M13 = Math::Multiply(M13, scalar);
            M14 = Math::Multiply(M14, scalar);

            M21 = Math::Multiply(M21, scalar);
            M22 = Math::Multiply(M22, scalar);
            M23 = Math::Multiply(M23, scalar);
            M24 = Math::Multiply(M24, scalar);

            M31 = Math::Multiply(M31, scalar);
            M32 = Math::Multiply(M32, scalar);
            M33 = Math::Multiply(M33, scalar);
            M34 = Math::Multiply(M34, scalar);

            M41 = Math::Multiply(M41, scalar);
            M42 = Math::Multiply(M42, scalar);
            M43 = Math::Multiply(M43, scalar);
            M44 = Math::Multiply(M44, scalar);

            return *this;
        }

        Matrix4x4 operator/(TScalar scalar) const
        {
            Matrix4x4 result = *this;
            result /= scalar;
            return result;
        }

        Matrix4x4& operator/=(TScalar scalar)
        {
            if (Math::ApproximatelyEqual(scalar, Math::Zero<TScalar>))
                return *this;

            M11 = Math::Divide(M11, scalar);
            M12 = Math::Divide(M12, scalar);
            M13 = Math::Divide(M13, scalar);
            M14 = Math::Divide(M14, scalar);

            M21 = Math::Divide(M21, scalar);
            M22 = Math::Divide(M22, scalar);
            M23 = Math::Divide(M23, scalar);
            M24 = Math::Divide(M24, scalar);

            M31 = Math::Divide(M31, scalar);
            M32 = Math::Divide(M32, scalar);
            M33 = Math::Divide(M33, scalar);
            M34 = Math::Divide(M34, scalar);

            M41 = Math::Divide(M41, scalar);
            M42 = Math::Divide(M42, scalar);
            M43 = Math::Divide(M43, scalar);
            M44 = Math::Divide(M44, scalar);

            return *this;
        }

        bool operator==(const Matrix4x4& other) const
        {
            return Math::ApproximatelyEqual(M11, other.M11) && Math::ApproximatelyEqual(M12, other.M12) && Math::ApproximatelyEqual(M13, other.M13) && Math::ApproximatelyEqual(M14, other.M14) &&
                   Math::ApproximatelyEqual(M21, other.M21) && Math::ApproximatelyEqual(M22, other.M22) && Math::ApproximatelyEqual(M23, other.M23) && Math::ApproximatelyEqual(M24, other.M24) &&
                   Math::ApproximatelyEqual(M31, other.M31) && Math::ApproximatelyEqual(M32, other.M32) && Math::ApproximatelyEqual(M33, other.M33) && Math::ApproximatelyEqual(M34, other.M34) &&
                   Math::ApproximatelyEqual(M41, other.M41) && Math::ApproximatelyEqual(M42, other.M42) && Math::ApproximatelyEqual(M43, other.M43) && Math::ApproximatelyEqual(M44, other.M44);
        }

        bool operator!=(const Matrix4x4& other) const
        {
            return !(*this == other);
        }

        TScalar Determinant() const
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