#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Span.hpp>
#include <Ryn/Core/Memory.hpp>

namespace Ryn::Collections
{
    template <typename TValue>
    class Vector
    {
      private:
        static constexpr Core::usz InitialCapacity = 4;

      private:
        TValue* _data{};
        Core::usz _count{};
        Core::usz _capacity{};

      public:
        consteval Vector() {}

        template <Core::usz N>
        constexpr Vector(const TValue (&array)[N]) :
            _count{N},
            _capacity{N}
        {
            _data = new TValue[_capacity];
            for (Core::usz index = 0; index < N; index += 1)
            {
                _data[index] = array[index];
            }
        }

        template <Core::usz N>
        constexpr Vector(TValue (&&array)[N]) :
            _count{N},
            _capacity{N}
        {
            _data = new TValue[_capacity];
            for (Core::usz index = 0; index < N; index += 1)
            {
                _data[index] = Core::Utility::Move(array[index]);
            }
        }

        constexpr Vector(Core::usz capacity) :
            _capacity{capacity}
        {
            _data = new TValue[_capacity];
        }

        constexpr Vector(const Vector& other) :
            _count{other._count},
            _capacity{other._capacity}
        {
            _data = new TValue[_capacity];
            Core::Memory::Copy(&_data[0], &other._data[0], _count);
        }

        constexpr Vector(Vector&& other) :
            _count{other._count},
            _capacity{other._capacity},
            _data{other._data}
        {
            other._count = 0;
            other._capacity = 0;
            other._data = nullptr;
        }

        constexpr ~Vector()
        {
            delete[] _data;
            _data = nullptr;
        }

        constexpr Vector& operator=(const Vector& other)
        {
            if (this != &other)
            {
                _count = other._count;
                _capacity = other._capacity;

                delete[] _data;
                _data = new TValue[_capacity];
                Core::Memory::Copy(&_data[0], &other._data[0], _count);
            }

            return *this;
        }

        constexpr Vector& operator=(Vector&& other)
        {
            if (this != &other)
            {
                _count = other._count;
                _capacity = other._capacity;
                _data = other._data;

                other._count = 0;
                other._capacity = 0;
                other._data = nullptr;
            }

            return *this;
        }

        Core::usz Count() const { return _count; }

        constexpr TValue& operator[](Core::usz index) { return _data[index]; }
        constexpr const TValue& operator[](Core::usz index) const { return _data[index]; }

        constexpr Core::Span<TValue> ToSpan() const { return Core::Span<TValue>(_data, _count); }
        constexpr Core::Span<TValue> ToSpan(Core::usz start) const { return ToSpan().Slice(start); }
        constexpr Core::Span<TValue> ToSpan(Core::usz start, Core::usz length) const { return ToSpan().Slice(start, length); }

        constexpr void Push(const TValue& value)
        {
            if (_count >= _capacity)
            {
                _capacity = (_capacity == 0) ? InitialCapacity : _capacity * 2;
                TValue* newData = new TValue[_capacity];
                Core::Memory::Copy(&newData[0], &_data[0], _count);
                delete[] _data;
                _data = newData;
            }

            _data[_count] = value;
            _count += 1;
        }

        constexpr void Push(TValue&& value)
        {
            if (_count >= _capacity)
            {
                _capacity = (_capacity == 0) ? InitialCapacity : _capacity * 2;
                TValue* newData = new TValue[_capacity];
                Core::Memory::Copy(&newData[0], &_data[0], _count);
                delete[] _data;
                _data = newData;
            }

            _data[_count] = Core::Utility::Move(value);
            _count += 1;
        }

        constexpr void Pop()
        {
            if (_count > 0)
            {
                _count -= 1;
            }
        }

        constexpr void Clear()
        {
            _count = 0;
        }
    };
}
