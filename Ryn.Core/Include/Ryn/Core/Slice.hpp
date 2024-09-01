#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Core
{
    template <typename T>
    class Slice
    {
      private:
        const T* _data{};
        usz _length{};

      public:
        constexpr Slice() {}

        constexpr Slice(const T* data, usz length) :
            _data(data),
            _length(length) {}

        template <usz N>
        constexpr Slice(const T (&data)[N]) :
            _data(data),
            _length(N) {}

        constexpr Slice(const Slice<T>& other) :
            _data(other._data),
            _length(other._length) {}

        constexpr Slice(Slice<T>&& other) noexcept :
            _data(other._data),
            _length(other._length)
        {
            other._data = nullptr;
            other._length = 0;
        }

        constexpr Slice<T>& operator=(const Slice<T>& other)
        {
            if (this != &other)
            {
                _data = other._data;
                _length = other._length;
            }

            return *this;
        }

        constexpr Slice<T>& operator=(Slice<T>&& other) noexcept
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

        constexpr const T& operator[](usz index) const { return _data[index]; }

        constexpr Slice<T> Cut(usz start) const
        {
            if (_data == nullptr || start >= _length)
                return Slice<T>{};

            return Slice<T>(_data + start, _length - start);
        }

        constexpr Slice<T> Cut(usz start, usz length) const
        {
            if (_data == nullptr || start >= _length || start + length > _length || length == 0)
                return Slice<T>{};

            return Slice<T>(_data + start, length);
        }
    };
}
