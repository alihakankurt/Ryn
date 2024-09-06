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
      private:
        static constexpr u32 InitialCapacity = 4;

      private:
        TValue* _data;
        u32 _count;
        u32 _capacity;

      public:
        consteval List() :
            _data{},
            _count{},
            _capacity{} {}

        template <u32 N>
        constexpr List(const TValue (&array)[N]) :
            _count{N},
            _capacity{N}
        {
            _data = new TValue[_capacity];
            for (u32 index = 0; index < N; index += 1)
            {
                _data[index] = array[index];
            }
        }

        template <u32 N>
        constexpr List(TValue (&&array)[N]) :
            _count{N},
            _capacity{N}
        {
            _data = new TValue[_capacity];
            for (u32 index = 0; index < N; index += 1)
            {
                _data[index] = Utility::Move(array[index]);
            }
        }

        constexpr List(u32 capacity) :
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

        u32 Count() const { return _count; }

        constexpr TValue& operator[](u32 index) { return _data[index]; }
        constexpr const TValue& operator[](u32 index) const { return _data[index]; }

        constexpr TValue& First() { return _data[0]; }
        constexpr const TValue& First() const { return _data[0]; }

        constexpr TValue& Last() { return _data[_count - 1]; }
        constexpr const TValue& Last() const { return _data[_count - 1]; }

        constexpr Span<TValue> ToSpan() const { return Span<TValue>{_data, _count}; }
        constexpr Span<TValue> ToSpan(u32 start) const { return ToSpan().Slice(start); }
        constexpr Span<TValue> ToSpan(u32 start, u32 length) const { return ToSpan().Slice(start, length); }

        constexpr void EnsureCapacity(u32 capacity)
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
            for (u32 index = 0; index < _count; index += 1)
            {
                if (_data[index] == value)
                {
                    RemoveAt(index);
                    return true;
                }
            }
            return false;
        }

        constexpr void RemoveAt(u32 index)
        {
            if (index >= _count)
                return;

            _count -= 1;
            for (u32 removeIndex = index; removeIndex < _count; removeIndex += 1)
            {
                _data[removeIndex] = _data[removeIndex + 1];
            }
        }

        constexpr void Clear()
        {
            _count = {};
        }
    };
}
