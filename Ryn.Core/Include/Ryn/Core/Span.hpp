#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Memory.hpp>

namespace Ryn::Core
{
    template <typename TValue>
    class Span
    {
      private:
        TValue* _data{};
        usz _length{};

      public:
        consteval Span() {}

        constexpr Span(TValue* data, usz length) :
            _data(data),
            _length(length) {}

        template <usz N>
        constexpr Span(TValue (&&data)[N]) :
            _data(data),
            _length(N) {}

        constexpr Span(const Span<TValue>& other) :
            _data(other._data),
            _length(other._length) {}

        constexpr Span(Span<TValue>&& other) :
            _data(other._data),
            _length(other._length)
        {
            other._data = nullptr;
            other._length = 0;
        }

        constexpr Span<TValue>& operator=(const Span<TValue>& other)
        {
            if (this != &other)
            {
                _data = other._data;
                _length = other._length;
            }

            return *this;
        }

        constexpr Span<TValue>& operator=(Span<TValue>&& other)
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

        constexpr TValue& operator[](usz index) { return _data[index]; }
        constexpr const TValue& operator[](usz index) const { return _data[index]; }

        constexpr operator Span<const TValue>() const { return Span<const TValue>(_data, _length); }

        constexpr Span<TValue> Slice(usz start) const
        {
            if (_data == nullptr || start >= _length)
                return Span<TValue>{};

            return Span<TValue>(_data + start, _length - start);
        }

        constexpr Span<TValue> Slice(usz start, usz length) const
        {
            if (_data == nullptr || start >= _length)
                return Span<TValue>{};

            if (start + length > _length || length == 0)
                return Span<TValue>{};

            return Span<TValue>(_data + start, length);
        }

        constexpr bool operator==(const Span<TValue>& other) const
        {
            return _length == other._length && Memory::Compare(_data, other._data, _length) == 0;
        }

        constexpr bool operator!=(const Span<TValue>& other) const
        {
            return !(*this == other);
        }

        constexpr bool operator<(const Span<TValue>& other) const
        {
            const usz length = (_length < other._length) ? _length : other._length;
            const isz comparison = Memory::Compare(_data, other._data, length);
            return (comparison == 0) ? _length < other._length : comparison < 0;
        }

        constexpr bool operator>(const Span<TValue>& other) const
        {
            const usz length = (_length < other._length) ? _length : other._length;
            const isz comparison = Memory::Compare(_data, other._data, length);
            return (comparison == 0) ? _length > other._length : comparison > 0;
        }

        constexpr bool operator<=(const Span<TValue>& other) const
        {
            return !(*this > other);
        }

        constexpr bool operator>=(const Span<TValue>& other) const
        {
            return !(*this < other);
        }
    };
}
