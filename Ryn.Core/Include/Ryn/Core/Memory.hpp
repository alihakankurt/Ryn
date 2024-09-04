#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Core::Memory
{
    template <typename TValue>
    static constexpr isz Compare(const TValue* source1, const TValue* source2, usz count)
    {
        if (count == 0 || source1 == source2)
            return 0;

        usz size = count * sizeof(TValue);
        const u8* src1 = reinterpret_cast<const u8*>(source1);
        const u8* src2 = reinterpret_cast<const u8*>(source2);

        while (size >= sizeof(isz))
        {
            if (isz difference = *reinterpret_cast<const isz*>(src1) - *reinterpret_cast<const isz*>(src2); difference != 0)
            {
                return difference;
            }

            src1 += sizeof(isz);
            src2 += sizeof(isz);
            size -= sizeof(isz);
        }

        while (size > 0)
        {
            if (isz difference = *src1 - *src2; difference != 0)
            {
                return difference;
            }

            src1 += sizeof(u8);
            src2 += sizeof(u8);
            size -= sizeof(u8);
        }

        return 0;
    }

    template <typename TValue>
    static constexpr void Copy(TValue* destination, const TValue* source, usz count)
    {
        if (count == 0 || destination == source)
            return;

        usz size = count * sizeof(TValue);
        u8* dst = reinterpret_cast<u8*>(destination);
        const u8* src = reinterpret_cast<const u8*>(source);

        if (destination < source)
        {
            while (size >= sizeof(usz))
            {
                *reinterpret_cast<usz*>(dst) = *reinterpret_cast<const usz*>(src);
                dst += sizeof(usz);
                src += sizeof(usz);
                size -= sizeof(usz);
            }

            while (size > 0)
            {
                *dst = *src;
                dst += sizeof(u8);
                src += sizeof(u8);
                size -= sizeof(u8);
            }
        }
        else
        {
            dst += size;
            src += size;

            while (size >= sizeof(usz))
            {
                dst -= sizeof(usz);
                src -= sizeof(usz);
                *reinterpret_cast<usz*>(dst) = *reinterpret_cast<const usz*>(src);
                size -= sizeof(usz);
            }

            while (size > 0)
            {
                dst -= sizeof(u8);
                src -= sizeof(u8);
                *dst = *src;
                size -= sizeof(u8);
            }
        }
    }

    template <typename TValue>
    static constexpr void Reverse(TValue* source, usz count)
    {
        if (count == 0)
            return;

        while (count > 1)
        {
            TValue temp = source[0];
            source[0] = source[count - 1];
            source[count - 1] = temp;
            source += 1;
            count -= 2;
        }
    }
}
