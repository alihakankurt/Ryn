#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Traits.hpp>
#include <Ryn/Core/Memory.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Function.hpp>
#include <Ryn/Core/Iterable.hpp>
#include <Ryn/Core/Span.hpp>

namespace Ryn
{
    template <typename TValue>
    class List : public Iterable<TValue, LinearIterator<TValue>, LinearIterator<const TValue>>
    {
      public:
        using ValueType = Traits::RemoveVolatile<TValue>;
        using IteratorType = LinearIterator<TValue>;
        using ConstIteratorType = LinearIterator<const TValue>;

        static_assert(!Traits::Reference<ValueType>, "Value type cannot be a reference!");
        static_assert(!Traits::Const<ValueType>, "Value type cannot be const-qualified!");

      private:
        static constexpr usz InitialCapacity = 4;

      private:
        usz _count;
        usz _capacity;
        ValueType* _data;

      public:
        constexpr List() :
            _count{},
            _capacity{},
            _data{} {}

        constexpr List(usz count, ValueType* data) :
            _count{count},
            _capacity{count},
            _data{data} {}

        template <usz N>
        List(const ValueType (&array)[N]) :
            _count{N},
            _capacity{N},
            _data{Memory::Allocate<ValueType>(N)}
        {
            for (usz index = 0; index < N; index += 1)
            {
                _data[index] = array[index];
            }
        }

        template <usz N>
        List(ValueType (&&array)[N]) :
            _count{N},
            _capacity{N},
            _data{Memory::Allocate<ValueType>(N)}
        {
            for (usz index = 0; index < N; index += 1)
            {
                _data[index] = Utility::Move(array[index]);
            }
        }

        List(usz capacity) :
            _count{capacity},
            _capacity{capacity},
            _data{Memory::Allocate<ValueType>(capacity)} {}

        List(const List& other) :
            _count{other._count},
            _capacity{other._capacity},
            _data{Memory::Allocate<ValueType>(other._capacity)}
        {
            for (usz index = 0; index < _count; index += 1)
            {
                _data[index] = other._data[index];
            }
        }

        constexpr List(List&& other) :
            _count{Utility::Exchange(other._count)},
            _capacity{Utility::Exchange(other._capacity)},
            _data{Utility::Exchange(other._data)} {}

        ~List()
        {
            Memory::Free<ValueType>(_data, _capacity);
            _count = 0;
            _capacity = 0;
            _data = {};
        }

        List& operator=(const List& other)
        {
            if (this != &other)
            {
                Memory::Free<ValueType>(_data, _capacity);

                _count = other._count;
                _capacity = other._capacity;
                _data = Memory::Allocate<ValueType>(other._capacity);
                for (usz index = 0; index < _count; index += 1)
                {
                    _data[index] = other._data[index];
                }
            }
            return *this;
        }

        List& operator=(List&& other)
        {
            if (this != &other)
            {
                Memory::Free<ValueType>(_data, _capacity);

                _count = Utility::Exchange(other._count);
                _capacity = Utility::Exchange(other._capacity);
                _data = Utility::Exchange(other._data);
            }
            return *this;
        }

        constexpr usz Count() const { return _count; }

        constexpr Span<ValueType> ToSpan() const { return Span<ValueType>{_data, _count}; }
        constexpr Span<ValueType> ToSpan(usz start) const { return ToSpan().Slice(start); }
        constexpr Span<ValueType> ToSpan(usz start, usz length) const { return ToSpan().Slice(start, length); }

        void Reserve(usz capacity)
        {
            if (_capacity >= capacity)
                return;

            ValueType* newData = Memory::Allocate<ValueType>(capacity);
            for (usz index = 0; index < _count; index += 1)
            {
                newData[index] = Utility::Move(_data[index]);
            }

            Memory::Free<ValueType>(_data, _capacity);

            _capacity = capacity;
            _data = newData;
        }

        void Add(const ValueType& value)
        {
            Reserve(_count + 1);
            _data[_count] = value;
            _count += 1;
        }

        void Add(ValueType&& value)
        {
            Reserve(_count + 1);
            _data[_count] = Utility::Move(value);
            _count += 1;
        }

        bool Remove(const ValueType& value)
        {
            for (usz index = 0; index < _count; index += 1)
            {
                if (_data[index] == value)
                {
                    RemoveAt(index);
                    return true;
                }
            }
            return false;
        }

        void RemoveAt(usz index)
        {
            if (index >= _count)
                return;

            _data[index].~ValueType();
            _count -= 1;

            for (usz removeIndex = index; removeIndex < _count; removeIndex += 1)
            {
                _data[removeIndex] = _data[removeIndex + 1];
            }
        }

        void Clear()
        {
            _count = 0;
        }

      public:
        constexpr IteratorType begin() override { return IteratorType{_data}; }
        constexpr ConstIteratorType begin() const override { return ConstIteratorType{_data}; }
        constexpr IteratorType end() override { return IteratorType{_data + _count}; }
        constexpr ConstIteratorType end() const override { return ConstIteratorType{_data + _count}; }
    };
}
