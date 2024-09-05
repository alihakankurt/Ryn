#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Core::Memory
{
    template <typename TValue>
    static constexpr i64 Compare(const TValue* source1, const TValue* source2, u32 count)
    {
        if (count == 0 || source1 == source2)
            return 0;

        u64 size = count * sizeof(TValue);
        const u8* src1 = reinterpret_cast<const u8*>(source1);
        const u8* src2 = reinterpret_cast<const u8*>(source2);

        while (size >= sizeof(i64))
        {
            if (i64 difference = *reinterpret_cast<const i64*>(src1) - *reinterpret_cast<const i64*>(src2); difference != 0)
            {
                return difference;
            }

            src1 += sizeof(i64);
            src2 += sizeof(i64);
            size -= sizeof(i64);
        }

        while (size > 0)
        {
            if (i64 difference = *src1 - *src2; difference != 0)
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
    static constexpr void Copy(TValue* destination, const TValue* source, u32 count)
    {
        if (count == 0 || destination == source)
            return;

        u64 size = count * sizeof(TValue);
        u8* dst = reinterpret_cast<u8*>(destination);
        const u8* src = reinterpret_cast<const u8*>(source);

        if (destination < source)
        {
            while (size >= sizeof(u64))
            {
                *reinterpret_cast<u64*>(dst) = *reinterpret_cast<const u64*>(src);
                dst += sizeof(u64);
                src += sizeof(u64);
                size -= sizeof(u64);
            }

            while (size >= sizeof(u8))
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

            while (size >= sizeof(u64))
            {
                dst -= sizeof(u64);
                src -= sizeof(u64);
                *reinterpret_cast<u64*>(dst) = *reinterpret_cast<const u64*>(src);
                size -= sizeof(u64);
            }

            while (size >= sizeof(u8))
            {
                dst -= sizeof(u8);
                src -= sizeof(u8);
                *dst = *src;
                size -= sizeof(u8);
            }
        }
    }

    template <typename TValue>
    static constexpr void Reverse(TValue* source, u32 count)
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
