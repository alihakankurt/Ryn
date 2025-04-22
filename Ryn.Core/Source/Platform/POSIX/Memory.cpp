#include <Ryn/Core/Memory.hpp>

#include <sys/mman.h>

namespace Ryn
{
    void* Memory::RawAllocate(usz size)
    {
        void* data = mmap({}, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (data == MAP_FAILED)
            data = {};

        return data;
    }

    void Memory::RawFree(const void* data, usz size)
    {
        munmap(const_cast<void*>(data), size);
    }
}
