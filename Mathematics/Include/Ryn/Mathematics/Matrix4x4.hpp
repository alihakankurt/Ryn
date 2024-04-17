#ifndef __RYN_MATHEMATICS_MATRIX4X4_HPP__
#define __RYN_MATHEMATICS_MATRIX4X4_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    template <typename TScalar>
    requires IsNumber<TScalar>
    struct Matrix4x4
    {
        TScalar Elements[4][4];

        TScalar& M11 = Elements[0][0];
        TScalar& M12 = Elements[0][1];
        TScalar& M13 = Elements[0][2];
        TScalar& M14 = Elements[0][3];
        TScalar& M21 = Elements[1][0];
        TScalar& M22 = Elements[1][1];
        TScalar& M23 = Elements[1][2];
        TScalar& M24 = Elements[1][3];
        TScalar& M31 = Elements[2][0];
        TScalar& M32 = Elements[2][1];
        TScalar& M33 = Elements[2][2];
        TScalar& M34 = Elements[2][3];
        TScalar& M41 = Elements[3][0];
        TScalar& M42 = Elements[3][1];
        TScalar& M43 = Elements[3][2];
        TScalar& M44 = Elements[3][3];

        Matrix4x4()
        {
            M11 = 1;
            M22 = 1;
            M33 = 1;
            M44 = 1;
        }

        Matrix4x4(const TScalar (&elements)[4][4])
        {
            for (usize i = 0; i < 4; i++)
                for (usize j = 0; j < 4; j++)
                    Elements[i][j] = elements[i][j];
        }

        Matrix4x4(const Matrix4x4& matrix)
        {
            for (usize i = 0; i < 4; i++)
                for (usize j = 0; j < 4; j++)
                    Elements[i][j] = matrix.Elements[i][j];
        }

        Matrix4x4& operator=(const Matrix4x4& matrix)
        {
            for (usize i = 0; i < 4; i++)
                for (usize j = 0; j < 4; j++)
                    Elements[i][j] = matrix.Elements[i][j];

            return *this;
        }

        Matrix4x4(const Matrix4x4&& matrix)
        {
            for (usize i = 0; i < 4; i++)
                for (usize j = 0; j < 4; j++)
                    Elements[i][j] = matrix.Elements[i][j];
        }

        Matrix4x4& operator=(const Matrix4x4&& matrix)
        {
            for (usize i = 0; i < 4; i++)
                for (usize j = 0; j < 4; j++)
                    Elements[i][j] = matrix.Elements[i][j];

            return *this;
        }

        Matrix4x4 operator+(const Matrix4x4& matrix) const
        {
            Matrix4x4 result;
            for (usize i = 0; i < 4; i++)
                for (usize j = 0; j < 4; j++)
                    result.Elements[i][j] = Elements[i][j] + matrix.Elements[i][j];

            return result;
        }

        Matrix4x4 operator-(const Matrix4x4& matrix) const
        {
            Matrix4x4 result;
            for (usize i = 0; i < 4; i++)
                for (usize j = 0; j < 4; j++)
                    result.Elements[i][j] = Elements[i][j] - matrix.Elements[i][j];

            return result;
        }
    };
}

#endif