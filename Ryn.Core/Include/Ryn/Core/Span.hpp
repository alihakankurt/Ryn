#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Memory.hpp>

namespace Ryn
{
    template <typename TValue>
    class Span
    {
      private:
        TValue* _data;
        u32 _length;

      public:
        consteval Span() :
            _data{},
            _length{} {}

        constexpr Span(TValue* data, u32 length) :
            _data{data},
            _length{length} {}

        template <u32 N>
        constexpr Span(TValue (&data)[N]) :
            _data{&data[0]},
            _length{N} {}

        constexpr Span(const Span<TValue>& other) :
            _data{other._data},
            _length{other._length} {}

        constexpr Span(Span<TValue>&& other) :
            _data{Utility::Exchange(other._data)},
            _length{Utility::Exchange(other._length)} {}

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
                _data = Utility::Exchange(other._data);
                _length = Utility::Exchange(other._length);
            }
            return *this;
        }

        constexpr u32 Length() const { return _length; }

        constexpr TValue& operator[](u32 index) { return _data[index]; }
        constexpr const TValue& operator[](u32 index) const { return _data[index]; }

        constexpr operator Span<const TValue>() const { return Span<const TValue>{_data, _length}; }

        constexpr Span<TValue> Slice(u32 start) const
        {
            if (!_data || start >= _length)
                return Span<TValue>{};

            return Span<TValue>{_data + start, _length - start};
        }

        constexpr Span<TValue> Slice(u32 start, u32 length) const
        {
            if (!_data || start >= _length)
                return Span<TValue>{};

            if (start + length > _length || length == 0)
                return Span<TValue>{};

            return Span<TValue>{_data + start, length};
        }

        constexpr bool operator==(const Span<TValue>& other) const
        {
            return _length == other._length && Memory::Compare(_data, other._data, _length) == 0;
        }

        constexpr bool operator!=(const Span<TValue>& other) const
        {
            return !(*this == other);
        }
    };
}
