#ifndef __RYN_CORE_CASTS_HPP__
#define __RYN_CORE_CASTS_HPP__

#include <Ryn/Core/Concepts.hpp>

namespace Ryn
{
    template <typename TOther, typename TSelf>
    static constexpr inline TOther As(const TSelf& value)
    {
        static_assert(!Is<TSelf, TOther>, "Cannot cast between the same types");
        return static_cast<TOther>(value);
    }

    template <Pointer TOther, Pointer TSelf>
    static constexpr inline TOther As(TSelf value)
    {
        static_assert(!Is<TSelf, TOther>, "Cannot cast between the same types");
        return reinterpret_cast<TOther>(value);
    }

    template <typename TSelf>
    static constexpr inline TSelf&& Move(TSelf&& value) noexcept
    {
        return As<RemoveReference<TSelf>&&>(value);
    }

    template <typename TSelf>
    static constexpr inline TSelf&& Forward(RemoveReference<TSelf>& value) noexcept
    {
        return As<TSelf&&>(value);
    }

    template <typename TSelf>
    static constexpr inline TSelf&& Forward(RemoveReference<TSelf>&& value) noexcept
    {
        return As<TSelf&&>(value);
    }

    template <Enum TEnum>
    static constexpr inline UnderlyingType<TEnum> operator+(TEnum self) noexcept
    {
        return As<UnderlyingType<TEnum>>(self);
    }

    template <Enum TEnum>
    static constexpr inline TEnum operator|(TEnum self, TEnum other) noexcept
    {
        return As<TEnum>(+self | +other);
    }
}

#endif