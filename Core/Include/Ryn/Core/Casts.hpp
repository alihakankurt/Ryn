#ifndef __RYN_CORE_CASTS_HPP__
#define __RYN_CORE_CASTS_HPP__

#include <Ryn/Core/Concepts.hpp>

namespace Ryn
{
    template <typename TOther, typename TSelf>
    static constexpr TOther As(const TSelf& value)
    {
        static_assert(!Is<TSelf, TOther>, "Cannot cast between the same types");
        return static_cast<TOther>(value);
    }

    template <Pointer TOther, Pointer TSelf>
    static constexpr TOther As(TSelf value)
    {
        static_assert(!Is<TSelf, TOther>, "Cannot cast between the same types");
        return reinterpret_cast<TOther>(value);
    }

    template <FunctionPointer TFunction>
    static constexpr TFunction As(void* handle)
    {
        return As<TFunction>(handle);
    }

    template <typename TSelf>
    static constexpr TSelf&& Move(TSelf&& value) noexcept
    {
        return As<RemoveReference<TSelf>&&>(value);
    }

    template <typename TSelf>
    static constexpr TSelf&& Forward(RemoveReference<TSelf>& value) noexcept
    {
        return As<TSelf&&>(value);
    }

    template <typename TSelf>
    static constexpr TSelf&& Forward(RemoveReference<TSelf>&& value) noexcept
    {
        return As<TSelf&&>(value);
    }

    template <Enum TEnum>
    static constexpr UnderlyingType<TEnum> operator+(TEnum self) noexcept
    {
        return As<UnderlyingType<TEnum>>(self);
    }

    template <Enum TEnum>
    static constexpr TEnum operator|(TEnum self, TEnum other) noexcept
    {
        return As<TEnum>(+self | +other);
    }
}

#endif