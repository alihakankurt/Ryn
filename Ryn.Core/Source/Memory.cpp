#include <Ryn/Core/Memory.hpp>

#include <string.h>

namespace Ryn::Core
{
    isz Memory::Compare(const void* source1, const void* source2, usz size)
    {
        return memcmp(source1, source2, size);
    }

    void Memory::Copy(void* destination, const void* source, usz size)
    {
        memcpy(destination, source, size);
    }

    void Memory::Move(void* destination, const void* source, usz size)
    {
        memmove(destination, source, size);
    }

    void Memory::Set(void* memory, u8 value, usz size)
    {
        memset(memory, value, size);
    }
}
