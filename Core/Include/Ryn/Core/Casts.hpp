#ifndef __RYN_CORE_CASTS_HPP__
#define __RYN_CORE_CASTS_HPP__

#include <Ryn/Core/Concepts.hpp>

namespace Ryn
{
    template <typename TOther, typename TSelf>
    static inline constexpr TOther As(const TSelf& value)
    {
        static_assert(!Is<TSelf, TOther>, "Cannot cast between the same types");
        if constexpr (Pointer<TSelf> != Pointer<TOther>)
            return reinterpret_cast<TOther>(value);
        else
            return static_cast<TOther>(value);
    }

    template <Pointer TOther, Pointer TSelf>
    static inline constexpr TOther As(TSelf value)
    {
        static_assert(!Is<TSelf, TOther>, "Cannot cast between the same types");
        return reinterpret_cast<TOther>(value);
    }

    template <typename TSelf>
    static inline constexpr RemoveReference<TSelf>&& Move(TSelf&& value)
    {
        return static_cast<RemoveReference<TSelf>&&>(value);
    }

    template <typename TSelf>
    static inline constexpr TSelf&& Forward(RemoveReference<TSelf>& value)
    {
        return static_cast<TSelf&&>(value);
    }

    template <typename TSelf>
    static inline constexpr TSelf&& Forward(RemoveReference<TSelf>&& value)
    {
        return static_cast<TSelf&&>(value);
    }

    template <Enum TEnum>
    static inline constexpr UnderlyingType<TEnum> operator+(TEnum self)
    {
        return As<UnderlyingType<TEnum>>(self);
    }

    template <Enum TEnum>
    static inline constexpr TEnum operator|(TEnum self, TEnum other)
    {
        return As<TEnum>(+self | +other);
    }
}

#endif