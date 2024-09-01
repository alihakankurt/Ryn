#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Memory.hpp>

namespace Ryn::Core
{
    template <typename T>
    class Span
    {
      private:
        T* _data{};
        usz _length{};

      public:
        consteval Span() {}

        constexpr Span(T* data, usz length) :
            _data(data),
            _length(length) {}

        template <usz N>
        constexpr Span(T (&data)[N]) :
            _data(data),
            _length(N - 1) {}

        Span(const Span<T>& other) :
            _data(other._data),
            _length(other._length) {}

        Span(Span<T>&& other) noexcept :
            _data(other._data),
            _length(other._length)
        {
            other._data = nullptr;
            other._length = 0;
        }

        Span<T>& operator=(const Span<T>& other)
        {
            if (this != &other)
            {
                _data = other._data;
                _length = other._length;
            }

            return *this;
        }

        Span<T>& operator=(Span<T>&& other) noexcept
        {
            if (this != &other)
            {
                _data = other._data;
                _length = other._length;

                other._data = nullptr;
                other._length = 0;
            }

            return *this;
        }

        constexpr usz Length() const { return _length; }
        constexpr const T* Raw() const { return _data; }

        constexpr T& operator[](usz index) { return _data[index]; }
        constexpr const T& operator[](usz index) const { return _data[index]; }

        constexpr operator Span<const T>() const { return Span<const T>(_data, _length); }

        Span<T> Cut(usz start) const
        {
            if (_data == nullptr || start >= _length)
                return Span<T>{};

            return Span<T>(_data + start, _length - start);
        }

        Span<T> Cut(usz start, usz length) const
        {
            if (_data == nullptr || start >= _length || start + length > _length || length == 0)
                return Span<T>{};

            return Span<T>(_data + start, length);
        }

        bool operator==(const Span<T>& other) const
        {
            return _length == other._length && Memory::Compare(_data, other._data, _length) == 0;
        }

        bool operator!=(const Span<T>& other) const
        {
            return !(*this == other);
        }

        bool operator<(const Span<T>& other) const
        {
            const usz length = (_length < other._length) ? _length : other._length;
            const isz comparison = Memory::Compare(_data, other._data, length);
            return (comparison == 0) ? _length < other._length : comparison < 0;
        }

        bool operator>(const Span<T>& other) const
        {
            const usz length = (_length < other._length) ? _length : other._length;
            const isz comparison = Memory::Compare(_data, other._data, length);
            return (comparison == 0) ? _length > other._length : comparison > 0;
        }

        bool operator<=(const Span<T>& other) const
        {
            return !(*this > other);
        }

        bool operator>=(const Span<T>& other) const
        {
            return !(*this < other);
        }
    };
}
