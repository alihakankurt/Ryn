#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Function.hpp>

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

        constexpr Iterator& operator++()
        {
            _ptr += 1;
            return *this;
        }

        constexpr Iterator& operator--()
        {
            _ptr -= 1;
            return *this;
        }

        constexpr Iterator& operator+=(isz offset)
        {
            _ptr += offset;
            return *this;
        }

        constexpr Iterator& operator-=(isz offset)
        {
            _ptr -= offset;
            return *this;
        }

        constexpr Iterator operator+(isz offset) const
        {
            Iterator it = *this;
            it += offset;
            return it;
        }

        constexpr Iterator operator-(isz offset) const
        {
            Iterator it = *this;
            it -= offset;
            return it;
        }

        constexpr isz operator-(const Iterator& other)
        {
            return static_cast<isz>(_ptr - other._ptr);
        }

        constexpr TValue& operator*() { return *_ptr; }
        constexpr const TValue& operator*() const { return *_ptr; }

        constexpr TValue* operator->() { return _ptr; }
        constexpr const TValue* operator->() const { return _ptr; }

        constexpr bool operator==(const Iterator& other) const { return _ptr == other._ptr; }
        constexpr bool operator!=(const Iterator& other) const { return _ptr != other._ptr; }
        constexpr bool operator<(const Iterator& other) const { return _ptr < other._ptr; }
        constexpr bool operator>(const Iterator& other) const { return _ptr > other._ptr; }
        constexpr bool operator<=(const Iterator& other) const { return _ptr <= other._ptr; }
        constexpr bool operator>=(const Iterator& other) const { return _ptr >= other._ptr; }
    };

    template <typename TValue>
    class Iterable
    {
      public:
        virtual Iterator<TValue> begin() = 0;
        virtual Iterator<const TValue> begin() const = 0;

        virtual Iterator<TValue> end() = 0;
        virtual Iterator<const TValue> end() const = 0;

      public:
        bool IsEmpty() const { return begin() == end(); }

        TValue& First() { return *begin(); }
        const TValue& First() const { return *begin(); }

        TValue& Last() { return *(end() - 1); }
        const TValue& Last() const { return *(end() - 1); }

        usz FindFirst(Predicate<TValue> predicate) const
        {
            for (Iterator<const TValue> it = begin(); it < end(); ++it)
                if (predicate(*it))
                    return static_cast<usz>(it - begin());

            return static_cast<usz>(-1);
        }

        usz FindLast(Predicate<TValue> predicate) const
        {
            if (IsEmpty())
                return static_cast<usz>(-1);

            for (Iterator<const TValue> it = end() - 1; it >= begin(); --it)
                if (predicate(*it))
                    return static_cast<usz>(it - begin());

            return static_cast<usz>(-1);
        }

        bool IfAny(Predicate<TValue> predicate) const
        {
            for (Iterator<const TValue> it = begin(); it < end(); ++it)
                if (predicate(*it))
                    return true;

            return false;
        }

        bool IfAll(Predicate<TValue> predicate) const
        {
            for (Iterator<const TValue> it = begin(); it < end(); ++it)
                if (!predicate(*it))
                    return false;

            return true;
        }
    };
}
