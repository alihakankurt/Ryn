#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Traits.hpp>
#include <Ryn/Core/Function.hpp>

namespace Ryn
{
    template <typename TValue>
    class Iterator
    {
      public:
        using ValueType = Traits::RemoveVolatile<TValue>;
        using MutableValueType = Traits::RemoveConst<ValueType>;

        static constexpr bool IsContiguous = false;

        template <typename TOther>
        friend class Iterator;

      protected:
        ValueType* Data;

      public:
        constexpr Iterator() :
            Data{} {}

        constexpr Iterator(ValueType* data) :
            Data(data) {}

        virtual Iterator& operator++() = 0;
        virtual Iterator& operator--() = 0;

        virtual Iterator& operator+=(usz offset) = 0;
        virtual Iterator& operator-=(usz offset) = 0;

        ValueType& operator*() { return *Data; }
        const ValueType& operator*() const { return *Data; }

        ValueType* operator->() { return Data; }
        const ValueType* operator->() const { return Data; }

        bool operator!() const { return !Data; }
        operator bool() const { return Data; }

        virtual bool operator==(const Iterator<MutableValueType>& other) const { return Data == other.Data; }
        virtual bool operator!=(const Iterator<MutableValueType>& other) const { return Data != other.Data; }

        virtual bool operator==(const Iterator<const MutableValueType>& other) const { return Data == other.Data; }
        virtual bool operator!=(const Iterator<const MutableValueType>& other) const { return Data != other.Data; }
    };

    template <typename TValue>
    class LinearIterator : public Iterator<TValue>
    {
      public:
        using ValueType = Traits::RemoveVolatile<TValue>;
        using MutableValueType = Traits::RemoveConst<ValueType>;

        static constexpr bool IsContiguous = true;

        template <typename TOther>
        friend class LinearIterator;

      public:
        constexpr LinearIterator() :
            Iterator<TValue>{} {}

        constexpr LinearIterator(ValueType* data) :
            Iterator<TValue>{data} {}

        LinearIterator& operator++() override
        {
            ++this->Data;
            return *this;
        }

        LinearIterator& operator--() override
        {
            --this->Data;
            return *this;
        }

        LinearIterator& operator+=(usz offset) override
        {
            this->Data += offset;
            return *this;
        }

        LinearIterator& operator-=(usz offset) override
        {
            this->Data -= offset;
            return *this;
        }

        bool operator<(const LinearIterator<MutableValueType>& other) const { return this->Data < other.Data; }
        bool operator>(const LinearIterator<MutableValueType>& other) const { return this->Data > other.Data; }
        bool operator<=(const LinearIterator<MutableValueType>& other) const { return this->Data <= other.Data; }
        bool operator>=(const LinearIterator<MutableValueType>& other) const { return this->Data >= other.Data; }

        bool operator<(const LinearIterator<const MutableValueType>& other) const { return this->Data < other.Data; }
        bool operator>(const LinearIterator<const MutableValueType>& other) const { return this->Data > other.Data; }
        bool operator<=(const LinearIterator<const MutableValueType>& other) const { return this->Data <= other.Data; }
        bool operator>=(const LinearIterator<const MutableValueType>& other) const { return this->Data >= other.Data; }
    };

    template <typename TValue, typename TIterator = Iterator<TValue>, typename TConstIterator = Iterator<const TValue>>
    class Iterable
    {
      public:
        using ValueType = Traits::RemoveVolatile<TValue>;

      public:
        virtual TIterator begin() = 0;
        virtual TConstIterator begin() const = 0;

        virtual TIterator end() = 0;
        virtual TConstIterator end() const = 0;

        TIterator Begin() { return begin(); }
        TConstIterator Begin() const { return begin(); }

        TIterator End() { return end(); }
        TConstIterator End() const { return end(); }

      public:
        bool IsEmpty() const { return begin() == end(); }

        ValueType* Data()
        {
            static_assert(TIterator::IsContiguous, "Data() is only available for contiguous iterators");
            return &*begin();
        }

        const ValueType* Data() const
        {
            static_assert(TConstIterator::IsContiguous, "Data() is only available for contiguous iterators");
            return &*begin();
        }

        ValueType& First() { return *begin(); }
        const ValueType& First() const { return *begin(); }

        ValueType& Last() { return *(end() -= 1); }
        const ValueType& Last() const { return *(end() -= 1); }

        ValueType& At(usz index) { return *(begin() += index); }
        const ValueType& At(usz index) const { return *(begin() += index); }

        ValueType& operator[](usz index) { return At(index); }
        const ValueType& operator[](usz index) const { return At(index); }

        TConstIterator FindFirst(const Predicate<ValueType>& predicate) const
        {
            TConstIterator it = begin();
            while (it != end())
            {
                if (predicate(*it))
                    return it;
                ++it;
            }

            return end();
        }

        TConstIterator FindLast(const Predicate<ValueType>& predicate) const
        {
            TConstIterator it = end();
            while (it != begin())
            {
                --it;
                if (predicate(*it))
                    return it;
            }

            return end();
        }

        bool IfAny(const Predicate<ValueType>& predicate) const
        {
            TConstIterator it = begin();
            while (it != end())
            {
                if (predicate(*it))
                    return true;
                ++it;
            }

            return false;
        }

        bool IfAll(const Predicate<TValue>& predicate) const
        {
            TConstIterator it = begin();
            while (it != end())
            {
                if (!predicate(*it))
                    return false;
                ++it;
            }

            return true;
        }
    };
}
