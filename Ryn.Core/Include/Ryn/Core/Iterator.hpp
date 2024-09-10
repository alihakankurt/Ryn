#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    template <typename TValue>
    class Iterator
    {
      private:
        TValue* _ptr;

      public:
        constexpr Iterator() :
            _ptr{} {}

        constexpr Iterator(TValue* ptr) :
            _ptr(ptr) {}

        constexpr Iterator& operator++() { _ptr += 1; return *this; }
        constexpr Iterator& operator--() { _ptr -= 1; return *this; }

        constexpr TValue& operator*() { return *_ptr; }
        constexpr const TValue& operator*() const { return *_ptr; }

        constexpr bool operator==(const Iterator& other) const { return _ptr == other._ptr; }
        constexpr bool operator!=(const Iterator& other) const { return _ptr != other._ptr; }
    };
}
