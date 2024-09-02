#pragma once

#include <Ryn/Core.hpp>

namespace Ryn::Collections
{
    template <typename TValue, Core::usz TLength>
    class Array
    {
      private:
        TValue _data[TLength];

      public:
        static_assert(TLength > 0, "The array cannot have a length of zero.");

        consteval Array() :
            _data{} {}

        constexpr Array(TValue (&&array)[TLength])
        {
            for (Core::usz index = 0; index < TLength; index += 1)
                _data[index] = Core::Utility::Move(array[index]);
        }

        constexpr Core::usz Length() const { return TLength; }

        constexpr TValue& operator[](Core::usz index) { return _data[index]; }
        constexpr const TValue& operator[](Core::usz index) const { return _data[index]; }
    };
}
