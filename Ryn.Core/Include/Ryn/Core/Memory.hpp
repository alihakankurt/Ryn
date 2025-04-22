#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Utility.hpp>

void* operator new(Ryn::usz size, void* data);
void* operator new[](Ryn::usz size, void* data);

namespace Ryn
{
    class Memory
    {
      public:
        Memory() = delete;
        ~Memory() = delete;

        template <typename TValue>
        static constexpr isz Compare(const TValue* source1, const TValue* source2, usz count)
        {
            if (!source1 || !source2 || count == 0 || source1 == source2)
                return 0;

            usz size = count * sizeof(TValue);
            const char* src1 = reinterpret_cast<const char*>(source1);
            const char* src2 = reinterpret_cast<const char*>(source2);

            while (size >= sizeof(usz))
            {
                isz difference = *reinterpret_cast<const isz*>(src1) - *reinterpret_cast<const isz*>(src2);
                if (difference != 0)
                {
                    return difference;
                }

                src1 += sizeof(usz);
                src2 += sizeof(usz);
                size -= sizeof(usz);
            }

            while (size >= sizeof(char))
            {
                isz difference = *src1 - *src2;
                if (difference != 0)
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
            if (!destination || !source || count == 0 || destination == source)
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
            if (!source || count == 0)
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

        template <typename TValue>
        static constexpr void Fill(TValue* destination, const TValue& value, usz count)
        {
            if (!destination || count == 0)
                return;

            usz size = count * sizeof(TValue);
            char* dst = reinterpret_cast<char*>(destination);

            while (size >= sizeof(usz))
            {
                *reinterpret_cast<usz*>(dst) = *reinterpret_cast<const usz*>(&value);
                dst += sizeof(usz);
                size -= sizeof(usz);
            }

            while (size >= sizeof(char))
            {
                *dst = *reinterpret_cast<const char*>(&value);
                dst += sizeof(char);
                size -= sizeof(char);
            }
        }

        template <typename TValue, typename... TArgs>
        static constexpr TValue* Construct(TValue* data, TArgs&&... args)
        {
            if (data)
            {
                new (data) TValue(Utility::Forward<TArgs>(args)...);
            }

            return data;
        }

        template <typename TValue, typename... TArgs>
        static constexpr TValue* Allocate(TArgs&&... args)
        {
            TValue* data = static_cast<TValue*>(Memory::RawAllocate(sizeof(TValue)));
            Memory::Construct(data, Utility::Forward<TArgs>(args)...);
            return data;
        }

        template <typename TValue>
        static constexpr void Free(const TValue* data)
        {
            if (!data)
                return;

            data->~TValue();
            Memory::RawFree(data, sizeof(TValue));
        }

        template <typename TValue>
        static constexpr TValue* Allocate(usz count)
        {
            if (count == 0)
                return {};

            usz size = count * sizeof(TValue);
            TValue* data = static_cast<TValue*>(Memory::RawAllocate(size));
            return data;
        }

        template <typename TValue>
        static constexpr void Free(const TValue* data, usz count)
        {
            if (!data || count == 0)
                return;

            for (usz index = 0; index < count; index += 1)
            {
                data[index].~TValue();
            }

            usz size = count * sizeof(TValue);
            Memory::RawFree(data, size);
        }

      private:
        static void* RawAllocate(usz size);
        static void RawFree(const void* data, usz size);
    };
}
