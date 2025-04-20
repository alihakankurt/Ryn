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

        template <typename TValue, typename TNewValue = TValue>
        static constexpr TValue Exchange(TValue& value, TNewValue&& newValue = {})
        {
            TValue oldValue = Utility::Move(value);
            value = Utility::Forward<TValue>(newValue);
            return oldValue;
        }

        template <typename TValue>
        static constexpr void Swap(TValue& value1, TValue& value2)
        {
            TValue temp = Utility::Move(value1);
            value1 = Utility::Move(value2);
            value2 = Utility::Move(temp);
        }
    }
}
