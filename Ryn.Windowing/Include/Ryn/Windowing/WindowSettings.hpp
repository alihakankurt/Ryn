#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/String.hpp>
#include <Ryn/Numerics/Vector2.hpp>

namespace Ryn
{
    struct WindowSettings
    {
        Vector2<u32> Size;
        String Title;
    };
}
