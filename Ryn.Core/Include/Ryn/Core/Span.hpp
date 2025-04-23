#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Traits.hpp>
#include <Ryn/Core/Memory.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Iterable.hpp>

namespace Ryn
{
    template <typename TValue>
    class Span : public Iterable<TValue, LinearIterator<TValue>, LinearIterator<const TValue>>
    {
      public:
        using ValueType = Traits::RemoveVolatile<TValue>;
        using IteratorType = LinearIterator<TValue>;
        using ConstIteratorType = LinearIterator<const TValue>;

        static_assert(!Traits::Reference<ValueType>, "Value type cannot be a reference!");

      private:
        usz _length;
        ValueType* _data;

      public:
        constexpr Span() :
            _length{},
            _data{} {}

        constexpr Span(usz length, ValueType* data) :
            _length{length},
            _data{data} {}

        template <usz N>
        constexpr Span(ValueType (&data)[N]) :
            _length{N},
            _data{data} {}

        template <usz N>
        constexpr Span(ValueType (&&data)[N]) :
            _length{N},
            _data{data} {}

        constexpr Span(const Span& other) :
            _length{other._length},
            _data{other._data} {}

        constexpr Span(Span&& other) :
            _length{Utility::Exchange(other._length)},
            _data{Utility::Exchange(other._data)} {}

        constexpr ~Span()
        {
            _length = 0;
            _data = {};
        }

        constexpr Span& operator=(const Span& other)
        {
            if (this != &other)
            {
                _length = other._length;
                _data = other._data;
            }
            return *this;
        }

        constexpr Span& operator=(Span&& other)
        {
            if (this != &other)
            {
                _length = Utility::Exchange(other._length);
                _data = Utility::Exchange(other._data);
            }
            return *this;
        }

        constexpr usz Length() const { return _length; }

        constexpr operator Span<const ValueType>() const { return Span<const ValueType>{_length, _data}; }

        constexpr Span Slice(usz start) const
        {
            if (!_data || start >= _length)
                return Span{};

            return Span{_length - start, _data + start};
        }

        constexpr Span Slice(usz start, usz length) const
        {
            if (!_data || start >= _length)
                return Span{};

            if (start + length > _length || length == 0)
                return Span{};

            return Span{length, _data + start};
        }

        constexpr bool operator==(const Span& other) const
        {
            return _length == other._length && Memory::Compare(_data, other._data, _length) == 0;
        }

        constexpr bool operator!=(const Span& other) const
        {
            return !(*this == other);
        }

      public:
        constexpr IteratorType begin() override { return IteratorType{_data}; }
        constexpr ConstIteratorType begin() const override { return ConstIteratorType{_data}; }
        constexpr IteratorType end() override { return IteratorType{_data + _length}; }
        constexpr ConstIteratorType end() const override { return ConstIteratorType{_data + _length}; }
    };
}
