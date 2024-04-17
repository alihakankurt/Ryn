#ifndef __RYN_MATHEMATICS_VECTOR_HPP__
#define __RYN_MATHEMATICS_VECTOR_HPP__

#include <Ryn/Mathematics/Vector2.hpp>
#include <Ryn/Mathematics/Vector3.hpp>

namespace Ryn
{
    struct Vector
    {
        template <typename TVector, typename TScalar, usize TSize>
        static constexpr TScalar LengthSquared(TVector vector)
        {
            TScalar result = 0;
            for (usize i = 0; i < TSize; i++)
                result += Math::Multiply<TScalar>(vector[i], vector[i]);
            return result;
        }

        template <typename TScalar>
        static constexpr TScalar LengthSquared(Vector2<TScalar> vector)
        {
            return LengthSquared<Vector2<TScalar>, TScalar, 2>(vector);
        }

        template <typename TScalar>
        static constexpr TScalar LengthSquared(Vector3<TScalar> vector)
        {
            return LengthSquared<Vector3<TScalar>, TScalar, 3>(vector);
        }

        template <typename TVector, typename TScalar, usize TSize>
        static constexpr TScalar Length(TVector vector)
        {
            return Math::Sqrt<TScalar>(LengthSquared<TVector, TScalar, TSize>(vector));
        }

        template <typename TScalar>
        static constexpr TScalar Length(Vector2<TScalar> vector)
        {
            return Length<Vector2<TScalar>, TScalar, 2>(vector);
        }

        template <typename TScalar>
        static constexpr TScalar Length(Vector3<TScalar> vector)
        {
            return Length<Vector3<TScalar>, TScalar, 3>(vector);
        }

        template <typename TVector, typename TScalar, usize TSize>
        static constexpr TVector Normalize(TVector vector)
        {
            TScalar length = Length<TVector, TScalar, TSize>(vector);
            if (length == 0)
                return vector;

            return vector / length;
        }

        template <typename TScalar>
        static constexpr Vector2<TScalar> Normalize(Vector2<TScalar> vector)
        {
            return Normalize<Vector2<TScalar>, TScalar, 2>(vector);
        }

        template <typename TScalar>
        static constexpr Vector3<TScalar> Normalize(Vector3<TScalar> vector)
        {
            return Normalize<Vector3<TScalar>, TScalar, 3>(vector);
        }

        template <typename TVector, typename TScalar, usize TSize>
        static constexpr TVector Lerp(TVector source, TVector target, TScalar time)
        {
            TVector result;
            for (usize i = 0; i < TSize; i++)
                result[i] = Math::Lerp<TScalar>(source[i], target[i], time);
            return result;
        }

        template <typename TScalar>
        static constexpr Vector2<TScalar> Lerp(Vector2<TScalar> source, Vector2<TScalar> target, TScalar time)
        {
            return Lerp<Vector2<TScalar>, TScalar, 2>(source, target, time);
        }

        template <typename TScalar>
        static constexpr Vector3<TScalar> Lerp(Vector3<TScalar> source, Vector3<TScalar> target, TScalar time)
        {
            return Lerp<Vector3<TScalar>, TScalar, 3>(source, target, time);
        }
    };
}

#endif