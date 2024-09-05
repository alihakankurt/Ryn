#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Span.hpp>

namespace Ryn::Collections
{
    template <typename TValue, Core::u32 TCount>
    class Array
    {
      private:
        TValue _data[TCount];

      public:
        static_assert(TCount > 0, "The array cannot be empty.");

        consteval Array() :
            _data{} {}

        constexpr Array(TValue (&&array)[TCount])
        {
            for (Core::u32 index = 0; index < TCount; index += 1)
                _data[index] = Core::Utility::Move(array[index]);
        }

        constexpr Core::u32 Count() const { return TCount; }

        constexpr TValue& operator[](Core::u32 index) { return _data[index]; }
        constexpr const TValue& operator[](Core::u32 index) const { return _data[index]; }

        constexpr operator Core::Span<TValue>() { return Core::Span<TValue>{&_data[0], TCount}; }
        constexpr operator Core::Span<const TValue>() const { return Core::Span<const TValue>{&_data[0], TCount}; }
    };
}
