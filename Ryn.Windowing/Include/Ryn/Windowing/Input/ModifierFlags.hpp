#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    enum class ModifierFlags
    {
        None = 0,
        Shift = 1 << 0,
        Control = 1 << 1,
        Alt = 1 << 2,
        System = 1 << 3,
        CapsLock = 1 << 4,
    };

    constexpr u32 operator+(ModifierFlags modifiers) { return static_cast<u32>(modifiers); }
    constexpr ModifierFlags operator~(ModifierFlags modifiers) { return static_cast<ModifierFlags>(~+modifiers); }

    constexpr ModifierFlags operator&(ModifierFlags left, ModifierFlags right) { return static_cast<ModifierFlags>(+left & +right); }
    constexpr ModifierFlags operator|(ModifierFlags left, ModifierFlags right) { return static_cast<ModifierFlags>(+left | +right); }
    constexpr ModifierFlags operator^(ModifierFlags left, ModifierFlags right) { return static_cast<ModifierFlags>(+left ^ +right); }

    constexpr ModifierFlags& operator&=(ModifierFlags& self, ModifierFlags other) { return self = self & other; }
    constexpr ModifierFlags& operator|=(ModifierFlags& self, ModifierFlags other) { return self = self | other; }
    constexpr ModifierFlags& operator^=(ModifierFlags& self, ModifierFlags other) { return self = self ^ other; }
}
