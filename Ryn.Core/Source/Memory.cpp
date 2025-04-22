#include <Ryn/Core/Memory.hpp>

void* operator new(Ryn::usz size, void* data)
{
    return data;
}

void* operator new[](Ryn::usz size, void* data)
{
    return data;
}
