#pragma once

#include <Ryn/Core/Traits.hpp>

namespace Ryn::Core::Utility
{
    template <typename TValue>
    static constexpr TValue&& Forward(RemoveReferenceType<TValue>& value)
    {
        return static_cast<TValue&&>(value);
    }

    template <typename TValue>
    static constexpr TValue&& Forward(RemoveReferenceType<TValue>&& value)
    {
        return static_cast<TValue&&>(value);
    }

    template <typename TValue>
    static constexpr RemoveReferenceType<TValue>&& Move(TValue&& value)
    {
        return static_cast<RemoveReferenceType<TValue>&&>(value);
    }

    template <typename TValue>
    static constexpr void Swap(TValue& item1, TValue& item2)
    {
        TValue temp = Move(item1);
        item1 = Move(item2);
        item2 = Move(temp);
    }
}