#pragma once

#include <Ryn/Core/Traits.hpp>

namespace Ryn
{
    namespace Utility
    {
        template <typename TValue>
        static constexpr TValue&& Forward(Traits::RemoveReference<TValue>& value)
        {
            return static_cast<TValue&&>(value);
        }

        template <typename TValue>
        static constexpr TValue&& Forward(Traits::RemoveReference<TValue>&& value)
        {
            return static_cast<TValue&&>(value);
        }

        template <typename TValue>
        static constexpr Traits::RemoveReference<TValue>&& Move(TValue&& value)
        {
            return static_cast<Traits::RemoveReference<TValue>&&>(value);
        }

        template <typename TValue>
        static constexpr TValue Exchange(TValue& value, TValue&& newValue = {})
        {
            TValue oldValue = Move(value);
            value = Forward<TValue>(newValue);
            return oldValue;
        }

        template <typename TValue>
        static constexpr void Swap(TValue& value1, TValue& value2)
        {
            TValue temp = Move(value1);
            value1 = Move(value2);
            value2 = Move(temp);
        }
    }
}
