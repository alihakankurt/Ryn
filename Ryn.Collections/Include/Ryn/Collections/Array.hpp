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
      public:
        using ValueType = Traits::RemoveVolatile<TValue>;
        using IteratorType = LinearIterator<TValue>;
        using ConstIteratorType = LinearIterator<const TValue>;

        static constexpr usz Count = TCount;

        static_assert(Count > 0, "Array cannot be empty!");
        static_assert(!Traits::Reference<ValueType>, "Value type cannot be a reference!");
        static_assert(!Traits::Const<ValueType>, "Value type cannot be a const-qualified!");

      private:
        ValueType _data[Count];

      public:
        constexpr Array() :
            _data{} {}

        constexpr Array(const ValueType& value)
        {
            for (usz index = 0; index < Count; index += 1)
                _data[index] = value;
        }

        constexpr Array(const ValueType (&array)[Count])
        {
            for (usz index = 0; index < Count; index += 1)
                _data[index] = array[index];
        }

        constexpr Array(ValueType (&&array)[Count])
        {
            for (usz index = 0; index < Count; index += 1)
                _data[index] = Utility::Move(array[index]);
        }

        constexpr Span<ValueType> ToSpan() const { return Span<ValueType>{_data, Count}; }
        constexpr Span<ValueType> ToSpan(usz start) const { return ToSpan().Slice(start); }
        constexpr Span<ValueType> ToSpan(usz start, usz length) const { return ToSpan().Slice(start, length); }

      public:
        constexpr IteratorType begin() override { return IteratorType{_data}; }
        constexpr ConstIteratorType begin() const override { return ConstIteratorType{_data}; }
        constexpr IteratorType end() override { return IteratorType{_data + Count}; }
        constexpr ConstIteratorType end() const override { return ConstIteratorType{_data + Count}; }
    };
}
