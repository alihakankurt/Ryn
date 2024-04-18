#ifndef __RYN_CORE_MEMORY_HPP__
#define __RYN_CORE_MEMORY_HPP__

#include <Ryn/Core/Types.hpp>

namespace Ryn::Memory
{
    template <typename T>
    static constexpr void Clear(T* destination, usize count) noexcept
    {
        Set(destination, T{}, count);
    }

    template <typename T>
    static constexpr void Set(T* destination, const T& value, usize count) noexcept
    {
        for (usize i = 0; i < count; ++i)
        {
            destination[i] = value;
        }
    }

    template <typename T>
    static constexpr void Copy(T* destination, const T* source, usize count) noexcept
    {
        for (usize i = 0; i < count; ++i)
        {
            destination[i] = source[i];
        }
    }
}

#endif