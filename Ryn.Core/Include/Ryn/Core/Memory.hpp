#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Core
{
    class Memory
    {
      public:
        static isz Compare(const void* source1, const void* source2, usz length);
        static void Copy(void* destination, const void* source, usz length);
        static void Move(void* destination, const void* source, usz length);
        static void Set(void* memory, u8 value, usz length);
    };
}
