#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Traits.hpp>
#include <Ryn/Core/Function.hpp>

namespace Ryn
{
    template <typename TValue>
    class Iterator
    {
      protected:
        TValue* Data;

        template <typename TOther>
        friend class Iterator;

      public:
        constexpr Iterator() :
            Data{} {}

        constexpr Iterator(TValue* data) :
            Data(data) {}

        virtual Iterator& operator++() = 0;
        virtual Iterator& operator--() = 0;

        virtual Iterator& operator+=(usz offset) = 0;
        virtual Iterator& operator-=(usz offset) = 0;

        TValue& operator*() { return *Data; }
        const TValue& operator*() const { return *Data; }

        TValue* operator->() { return Data; }
        const TValue* operator->() const { return Data; }

        bool operator!() const { return !Data; }
        operator bool() const { return Data; }

        virtual bool operator==(const Iterator<Traits::RemoveConst<TValue>>& other) const { return Data == other.Data; }
        virtual bool operator!=(const Iterator<Traits::RemoveConst<TValue>>& other) const { return Data != other.Data; }

        virtual bool operator==(const Iterator<const Traits::RemoveConst<TValue>>& other) const { return Data == other.Data; }
        virtual bool operator!=(const Iterator<const Traits::RemoveConst<TValue>>& other) const { return Data != other.Data; }
    };

    template <typename TValue>
    class LinearIterator : public Iterator<TValue>
    {
      public:
        constexpr LinearIterator() :
            Iterator<TValue>{} {}

        constexpr LinearIterator(TValue* data) :
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

        bool operator<(const LinearIterator<Traits::RemoveConst<TValue>>& other) const { return this->Data < other.Data; }
        bool operator>(const LinearIterator<Traits::RemoveConst<TValue>>& other) const { return this->Data > other.Data; }
        bool operator<=(const LinearIterator<Traits::RemoveConst<TValue>>& other) const { return this->Data <= other.Data; }
        bool operator>=(const LinearIterator<Traits::RemoveConst<TValue>>& other) const { return this->Data >= other.Data; }

        bool operator<(const LinearIterator<const Traits::RemoveConst<TValue>>& other) const { return this->Data < other.Data; }
        bool operator>(const LinearIterator<const Traits::RemoveConst<TValue>>& other) const { return this->Data > other.Data; }
        bool operator<=(const LinearIterator<const Traits::RemoveConst<TValue>>& other) const { return this->Data <= other.Data; }
        bool operator>=(const LinearIterator<const Traits::RemoveConst<TValue>>& other) const { return this->Data >= other.Data; }
    };

    template <typename TValue, typename TIterator = Iterator<TValue>, typename TConstIterator = Iterator<const TValue>>
    class Iterable
    {
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

        TValue* Data()
        {
            static_assert(Traits::Same<TIterator, LinearIterator<TValue>>, "Data() can only be called on linear iterators");
            return &*begin();
        }

        const TValue* Data() const
        {
            static_assert(Traits::Same<TConstIterator, LinearIterator<const TValue>>, "Data() can only be called on linear iterators");
            return &*begin();
        }

        TValue& First() { return *begin(); }
        const TValue& First() const { return *begin(); }

        TValue& Last() { return *(end() -= 1); }
        const TValue& Last() const { return *(end() -= 1); }

        TValue& At(usz index) { return *(begin() += index); }
        const TValue& At(usz index) const { return *(begin() += index); }

        TValue& operator[](usz index) { return At(index); }
        const TValue& operator[](usz index) const { return At(index); }

        TConstIterator FindFirst(Predicate<TValue> predicate) const
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

        TConstIterator FindLast(Predicate<TValue> predicate) const
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

        bool IfAny(Predicate<TValue> predicate) const
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

        bool IfAll(Predicate<TValue> predicate) const
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
