#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    namespace Memory
    {
        template <typename TValue>
        static constexpr isz Compare(const TValue* source1, const TValue* source2, usz count)
        {
            if (count == 0 || source1 == source2)
                return 0;

            usz size = count * sizeof(TValue);
            const char* src1 = reinterpret_cast<const char*>(source1);
            const char* src2 = reinterpret_cast<const char*>(source2);

            while (size >= sizeof(usz))
            {
                if (isz difference = *reinterpret_cast<const isz*>(src1) - *reinterpret_cast<const isz*>(src2); difference != 0)
                {
                    return difference;
                }

                src1 += sizeof(usz);
                src2 += sizeof(usz);
                size -= sizeof(usz);
            }

            while (size >= sizeof(char))
            {
                if (isz difference = *src1 - *src2; difference != 0)
                {
                    return difference;
                }

                src1 += sizeof(char);
                src2 += sizeof(char);
                size -= sizeof(char);
            }

            return 0;
        }

        template <typename TValue>
        static constexpr void Copy(TValue* destination, const TValue* source, usz count)
        {
            if (count == 0 || destination == source)
                return;

            usz size = count * sizeof(TValue);
            char* dst = reinterpret_cast<char*>(destination);
            const char* src = reinterpret_cast<const char*>(source);

            if (destination < source)
            {
                while (size >= sizeof(usz))
                {
                    *reinterpret_cast<usz*>(dst) = *reinterpret_cast<const usz*>(src);
                    dst += sizeof(usz);
                    src += sizeof(usz);
                    size -= sizeof(usz);
                }

                while (size >= sizeof(char))
                {
                    *dst = *src;
                    dst += sizeof(char);
                    src += sizeof(char);
                    size -= sizeof(char);
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

                while (size >= sizeof(char))
                {
                    dst -= sizeof(char);
                    src -= sizeof(char);
                    *dst = *src;
                    size -= sizeof(char);
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
}
