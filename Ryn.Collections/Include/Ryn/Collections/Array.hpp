#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Iterator.hpp>
#include <Ryn/Core/Span.hpp>

namespace Ryn
{
    template <typename TValue, usz TCount>
    class Array
    {
        static_assert(TCount > 0, "Array cannot be empty.");
        static_assert(!Traits::Reference<TValue>, "Value type cannot be a reference.");
        static_assert(!Traits::Const<TValue>, "Value type cannot be const-qualified.");

      private:
        TValue _data[TCount];

      public:
        constexpr Array() :
            _data{} {}

        constexpr Array(const TValue& value)
        {
            for (usz index = 0; index < TCount; index += 1)
                _data[index] = value;
        }

        constexpr Array(const TValue (&array)[TCount])
        {
            for (usz index = 0; index < TCount; index += 1)
                _data[index] = array[index];
        }

        constexpr Array(TValue (&&array)[TCount])
        {
            for (usz index = 0; index < TCount; index += 1)
                _data[index] = Utility::Move(array[index]);
        }

        constexpr usz Count() const { return TCount; }

        constexpr TValue& operator[](usz index) { return _data[index]; }
        constexpr const TValue& operator[](usz index) const { return _data[index]; }

        constexpr operator Span<TValue>() { return Span<TValue>{&_data[0], TCount}; }
        constexpr operator Span<const TValue>() const { return Span<const TValue>{&_data[0], TCount}; }

      public:
        constexpr Iterator<TValue> begin() { return Iterator<TValue>{_data}; }
        constexpr Iterator<const TValue> begin() const { return Iterator<const TValue>{_data}; }
        constexpr Iterator<TValue> end() { return Iterator<TValue>{_data + TCount}; }
        constexpr Iterator<const TValue> end() const { return Iterator<const TValue>{_data + TCount}; }
    };
}
