#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Core
{
    class Memory
    {
      public:
        template <typename TValue>
        static constexpr isz Compare(const TValue* source1, const TValue* source2, usz count)
        {
            if (count == 0 || source1 == source2)
                return 0;

            usz size = count * sizeof(TValue);
            while (size >= sizeof(isz))
            {
                isz difference = *reinterpret_cast<const isz*>(source1) - *reinterpret_cast<const isz*>(source2);
                if (difference != 0)
                    return difference;

                source1 += sizeof(isz);
                source2 += sizeof(isz);
                size -= sizeof(isz);
            }

            while (size > 0)
            {
                isz difference = *reinterpret_cast<const i8*>(source1) - *reinterpret_cast<const i8*>(source2);
                if (difference != 0)
                    return difference;

                source1 += sizeof(i8);
                source2 += sizeof(i8);
                size -= sizeof(i8);
            }

            return 0;
        }

        template <typename TValue>
        static constexpr void Copy(TValue* destination, const TValue* source, usz count)
        {
            if (count == 0 || destination == source)
                return;

            usz size = count * sizeof(TValue);
            if (destination < source)
            {
                while (size >= sizeof(usz))
                {
                    *reinterpret_cast<usz*>(destination) = *reinterpret_cast<const usz*>(source);
                    destination += sizeof(usz);
                    source += sizeof(usz);
                    size -= sizeof(usz);
                }

                while (size > 0)
                {
                    *reinterpret_cast<u8*>(destination) = *reinterpret_cast<const u8*>(source);
                    destination += sizeof(u8);
                    source += sizeof(u8);
                    size -= sizeof(u8);
                }
            }
            else
            {
                destination += size;
                source += size;

                while (size >= sizeof(usz))
                {
                    destination -= sizeof(usz);
                    source -= sizeof(usz);
                    *reinterpret_cast<usz*>(destination) = *reinterpret_cast<const usz*>(source);
                    size -= sizeof(usz);
                }

                while (size > 0)
                {
                    destination -= sizeof(u8);
                    source -= sizeof(u8);
                    *reinterpret_cast<u8*>(destination) = *reinterpret_cast<const u8*>(source);
                    size -= sizeof(u8);
                }
            }
        }
    };
}
