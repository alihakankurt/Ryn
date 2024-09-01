#include <Ryn/Core/Memory.hpp>

#include <string.h>

namespace Ryn::Core
{
    isz Memory::Compare(const void* source1, const void* source2, usz length)
    {
        return memcmp(source1, source2, length);
    }

    void Memory::Copy(void* destination, const void* source, usz length)
    {
        memcpy(destination, source, length);
    }

    void Memory::Move(void* destination, const void* source, usz length)
    {
        memmove(destination, source, length);
    }

    void Memory::Set(void* memory, u8 value, usz length)
    {
        memset(memory, value, length);
    }
}
