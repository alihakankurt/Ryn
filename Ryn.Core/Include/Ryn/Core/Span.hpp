#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Traits.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Memory.hpp>
#include <Ryn/Core/Iterator.hpp>

namespace Ryn
{
    template <typename TValue>
    class Span
    {
        static_assert(!Traits::Reference<TValue>, "Value type cannot be a reference.");

      private:
        TValue* _data;
        u32 _length;

      public:
        constexpr Span() :
            _data{},
            _length{} {}

        constexpr Span(TValue* data, u32 length) :
            _data{data},
            _length{length} {}

        template <u32 N>
        constexpr Span(TValue (&data)[N]) :
            _data{&data[0]},
            _length{N} {}

        template <u32 N>
        constexpr Span(TValue (&&data)[N]) :
            _data{&data[0]},
            _length{N} {}

        constexpr Span(const Span& other) :
            _data{other._data},
            _length{other._length} {}

        constexpr Span(Span<TValue>&& other) :
            _data{Utility::Exchange(other._data)},
            _length{Utility::Exchange(other._length)} {}

        constexpr Span& operator=(const Span& other)
        {
            if (this != &other)
            {
                _data = other._data;
                _length = other._length;
            }
            return *this;
        }

        constexpr Span& operator=(Span<TValue>&& other)
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

        constexpr Span Slice(u32 start) const
        {
            if (!_data || start >= _length)
                return Span{};

            return Span{_data + start, _length - start};
        }

        constexpr Span Slice(u32 start, u32 length) const
        {
            if (!_data || start >= _length)
                return Span{};

            if (start + length > _length || length == 0)
                return Span{};

            return Span{_data + start, length};
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
        constexpr Iterator<TValue> begin() { return Iterator<TValue>{_data}; }
        constexpr Iterator<const TValue> begin() const { return Iterator<const TValue>{_data}; }
        constexpr Iterator<TValue> end() { return Iterator<TValue>{_data + _length}; }
        constexpr Iterator<const TValue> end() const { return Iterator<const TValue>{_data + _length}; }
    };
}
