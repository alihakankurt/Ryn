#ifndef __RYN_CORE_MEMORY_HPP__
#define __RYN_CORE_MEMORY_HPP__

#include <Ryn/Core/Types.hpp>

namespace Ryn::Memory
{
    template <typename TItem>
    static inline constexpr void Clear(TItem* destination, usize count)
    {
        for (usize index = 0; index < count; index += 1)
        {
            destination[index] = TItem{};
        }
    }

    template <typename TItem>
    static inline constexpr void Set(TItem* destination, const TItem& value, usize count)
    {
        for (usize index = 0; index < count; index += 1)
        {
            destination[index] = value;
        }
    }

    template <typename TItem>
    static inline constexpr void Copy(TItem* destination, const TItem* source, usize count)
    {
        for (usize index = 0; index < count; index += 1)
        {
            destination[index] = source[index];
        }
    }

    template <typename TItem>
    static inline constexpr void Shift(TItem* source, usize count, isize offset)
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