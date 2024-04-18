#ifndef __RYN_CORE_MEMORY_HPP__
#define __RYN_CORE_MEMORY_HPP__

#include <Ryn/Core/Types.hpp>

namespace Ryn::Memory
{
    template <typename TItem>
    static constexpr inline void Clear(TItem* destination, usize count) noexcept
    {
        Set(destination, TItem{}, count);
    }

    template <typename TItem>
    static constexpr inline void Set(TItem* destination, const TItem& value, usize count) noexcept
    {
        for (usize index = 0; index < count; index += 1)
        {
            destination[index] = value;
        }
    }

    template <typename TItem>
    static constexpr inline void Copy(TItem* destination, const TItem* source, usize count) noexcept
    {
        for (usize index = 0; index < count; index += 1)
        {
            destination[index] = source[index];
        }
    }

    template <typename TItem>
    static constexpr inline void Shift(TItem* source, usize count, isize offset) noexcept
    {
        source = (offset < 0) ? source : source + count - 1;
        isize direction = (offset < 0) ? 1 : -1;
        TItem* destination = source + offset;
        while (count > 0)
        {
            *destination = *source;
            destination += direction;
            source += direction;
            count -= 1;
        }
    }
}

#endif