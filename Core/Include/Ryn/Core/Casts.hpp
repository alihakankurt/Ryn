#ifndef __RYN_CORE_CASTS_HPP__
#define __RYN_CORE_CASTS_HPP__

#include <Ryn/Core/Concepts.hpp>

namespace Ryn
{
    template <typename TOther, typename TSelf>
    requires (IsValueType<TSelf> && IsValueType<TOther>)
    static constexpr TOther As(TSelf value)
    {
        return static_cast<TOther>(value);
    }

    template <typename TOther, typename TSelf>
    requires (!IsValueType<TSelf> && !IsValueType<TOther>)
    static constexpr TOther As(const TSelf& value) noexcept
    {
        return static_cast<TOther>(value);
    }

    template <typename TOther, typename TSelf>
    static constexpr TOther As(TSelf& value) noexcept
    {
        return static_cast<TOther>(value);
    }

    template <typename TSelf>
    requires IsFunction<TSelf>
    static constexpr TSelf As(void* handle)
    {
        return reinterpret_cast<TSelf>(handle);
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

    template <typename TSelf>
    requires IsEnum<TSelf>
    static constexpr UnderlyingType<TSelf> operator+(TSelf self) noexcept
    {
        return As<UnderlyingType<TSelf>>(self);
    }

    template <typename TSelf>
    requires IsEnum<TSelf>
    static constexpr TSelf operator|(TSelf self, TSelf other) noexcept
    {
        return As<TSelf>(+self | +other);
    }
}

#endif