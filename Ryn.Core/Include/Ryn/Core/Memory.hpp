#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Core
{
    class Memory
    {
      public:
        static isz Compare(const void* source1, const void* source2, usz size);
        static void Copy(void* destination, const void* source, usz size);
        static void Move(void* destination, const void* source, usz size);
        static void Set(void* memory, u8 value, usz size);
    };
}
