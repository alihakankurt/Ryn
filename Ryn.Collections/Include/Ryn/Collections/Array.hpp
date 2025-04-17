#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Iterable.hpp>
#include <Ryn/Core/Span.hpp>

namespace Ryn
{
    template <typename TValue, usz TCount>
    class Array : public Iterable<TValue, LinearIterator<TValue>, LinearIterator<const TValue>>
    {
        static_assert(TCount > 0, "Array cannot be empty!");
        static_assert(!Traits::Reference<TValue>, "Value type cannot be a reference!");
        static_assert(!Traits::Const<TValue>, "Value type cannot be const-qualified!");

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

        constexpr operator Span<TValue>() { return Span<TValue>{&_data[0], TCount}; }
        constexpr operator Span<const TValue>() const { return Span<const TValue>{&_data[0], TCount}; }

      public:
        constexpr LinearIterator<TValue> begin() override { return LinearIterator<TValue>{_data}; }
        constexpr LinearIterator<const TValue> begin() const override { return LinearIterator<const TValue>{_data}; }
        constexpr LinearIterator<TValue> end() override { return LinearIterator<TValue>{_data + TCount}; }
        constexpr LinearIterator<const TValue> end() const override { return LinearIterator<const TValue>{_data + TCount}; }
    };
}
