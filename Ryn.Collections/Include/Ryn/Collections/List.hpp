#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Memory.hpp>
#include <Ryn/Core/Span.hpp>

namespace Ryn
{
    template <typename TValue>
    class List
    {
        static_assert(!Traits::Reference<TValue>, "Value type cannot be a reference.");
        static_assert(!Traits::Const<TValue>, "Value type cannot be const-qualified.");

      private:
        static constexpr usz InitialCapacity = 4;

      private:
        TValue* _data;
        usz _count;
        usz _capacity;

      public:
        constexpr List() :
            _data{},
            _count{},
            _capacity{} {}

        constexpr List(TValue* data, usz count) :
            _data{data},
            _count{count},
            _capacity{count} {}

        template <usz N>
        constexpr List(const TValue (&array)[N]) :
            _count{N},
            _capacity{N}
        {
            _data = new TValue[_capacity];
            for (usz index = 0; index < N; index += 1)
            {
                _data[index] = array[index];
            }
        }

        template <usz N>
        constexpr List(TValue (&&array)[N]) :
            _count{N},
            _capacity{N}
        {
            _data = new TValue[_capacity];
            for (usz index = 0; index < N; index += 1)
            {
                _data[index] = Utility::Move(array[index]);
            }
        }

        constexpr List(usz capacity) :
            _count{},
            _capacity{capacity}
        {
            _data = new TValue[_capacity];
        }

        constexpr List(const List& other) :
            _count{other._count},
            _capacity{other._capacity}
        {
            _data = new TValue[_capacity];
            Memory::Copy(&_data[0], &other._data[0], _count);
        }

        constexpr List(List&& other) :
            _data{Utility::Exchange(other._data)},
            _count{Utility::Exchange(other._count)},
            _capacity{Utility::Exchange(other._capacity)} {}

        constexpr ~List()
        {
            delete[] _data;
            _data = {};
            _count = {};
            _capacity = {};
        }

        constexpr List& operator=(const List& other)
        {
            if (this != &other)
            {
                delete[] _data;
                _data = new TValue[_capacity];
                Memory::Copy(&_data[0], &other._data[0], _count);

                _count = other._count;
                _capacity = other._capacity;
            }
            return *this;
        }

        constexpr List& operator=(List&& other)
        {
            if (this != &other)
            {
                delete[] _data;
                _data = Utility::Exchange(other._data);
                _count = Utility::Exchange(other._count);
                _capacity = Utility::Exchange(other._capacity);
            }
            return *this;
        }

        usz Count() const { return _count; }

        constexpr TValue& operator[](usz index) { return _data[index]; }
        constexpr const TValue& operator[](usz index) const { return _data[index]; }

        constexpr TValue& First() { return _data[0]; }
        constexpr const TValue& First() const { return _data[0]; }

        constexpr TValue& Last() { return _data[_count - 1]; }
        constexpr const TValue& Last() const { return _data[_count - 1]; }

        constexpr Span<TValue> ToSpan() const { return Span<TValue>{_data, _count}; }
        constexpr Span<TValue> ToSpan(usz start) const { return ToSpan().Slice(start); }
        constexpr Span<TValue> ToSpan(usz start, usz length) const { return ToSpan().Slice(start, length); }

        constexpr void EnsureCapacity(usz capacity)
        {
            if (_capacity >= capacity)
                return;

            _capacity = capacity;
            TValue* newData = new TValue[_capacity];
            Memory::Copy(&newData[0], &_data[0], _count);
            delete[] _data;
            _data = newData;
        }

        constexpr void Add(const TValue& value)
        {
            EnsureCapacity(_count + 1);
            _data[_count] = value;
            _count += 1;
        }

        constexpr void Add(TValue&& value)
        {
            EnsureCapacity(_count + 1);
            _data[_count] = Utility::Move(value);
            _count += 1;
        }

        constexpr bool Remove(const TValue& value)
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

        constexpr void RemoveAt(usz index)
        {
            if (index >= _count)
                return;

            _count -= 1;
            for (usz removeIndex = index; removeIndex < _count; removeIndex += 1)
            {
                _data[removeIndex] = _data[removeIndex + 1];
            }
        }

        constexpr void Clear()
        {
            _count = {};
        }

      public:
        constexpr Iterator<TValue> begin() { return Iterator<TValue>{_data}; }
        constexpr Iterator<const TValue> begin() const { return Iterator<const TValue>{_data}; }
        constexpr Iterator<TValue> end() { return Iterator<TValue>{_data + _count}; }
        constexpr Iterator<const TValue> end() const { return Iterator<const TValue>{_data + _count}; }
    };
}
