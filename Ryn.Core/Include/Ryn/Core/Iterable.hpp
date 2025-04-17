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

        virtual constexpr Iterator& operator++() = 0;
        virtual constexpr Iterator& operator--() = 0;

        virtual constexpr Iterator& operator+=(usz offset) = 0;
        virtual constexpr Iterator& operator-=(usz offset) = 0;

        constexpr TValue& operator*() { return *Data; }
        constexpr const TValue& operator*() const { return *Data; }

        constexpr TValue* operator->() { return Data; }
        constexpr const TValue* operator->() const { return Data; }

        constexpr bool operator!() const { return !Data; }
        constexpr operator bool() const { return Data; }

        virtual constexpr bool operator==(const Iterator<Traits::RemoveConst<TValue>>& other) const { return Data == other.Data; }
        virtual constexpr bool operator!=(const Iterator<Traits::RemoveConst<TValue>>& other) const { return Data != other.Data; }

        virtual constexpr bool operator==(const Iterator<const Traits::RemoveConst<TValue>>& other) const { return Data == other.Data; }
        virtual constexpr bool operator!=(const Iterator<const Traits::RemoveConst<TValue>>& other) const { return Data != other.Data; }
    };

    template <typename TValue>
    class LinearIterator : public Iterator<TValue>
    {
      public:
        constexpr LinearIterator() :
            Iterator<TValue>{} {}

        constexpr LinearIterator(TValue* data) :
            Iterator<TValue>{data} {}

        constexpr LinearIterator& operator++() override
        {
            ++this->Data;
            return *this;
        }

        constexpr LinearIterator& operator--() override
        {
            --this->Data;
            return *this;
        }

        constexpr LinearIterator& operator+=(usz offset) override
        {
            this->Data += offset;
            return *this;
        }

        constexpr LinearIterator& operator-=(usz offset) override
        {
            this->Data -= offset;
            return *this;
        }

        constexpr bool operator<(const LinearIterator<Traits::RemoveConst<TValue>>& other) const { return this->Data < other.Data; }
        constexpr bool operator>(const LinearIterator<Traits::RemoveConst<TValue>>& other) const { return this->Data > other.Data; }
        constexpr bool operator<=(const LinearIterator<Traits::RemoveConst<TValue>>& other) const { return this->Data <= other.Data; }
        constexpr bool operator>=(const LinearIterator<Traits::RemoveConst<TValue>>& other) const { return this->Data >= other.Data; }

        constexpr bool operator<(const LinearIterator<const Traits::RemoveConst<TValue>>& other) const { return this->Data < other.Data; }
        constexpr bool operator>(const LinearIterator<const Traits::RemoveConst<TValue>>& other) const { return this->Data > other.Data; }
        constexpr bool operator<=(const LinearIterator<const Traits::RemoveConst<TValue>>& other) const { return this->Data <= other.Data; }
        constexpr bool operator>=(const LinearIterator<const Traits::RemoveConst<TValue>>& other) const { return this->Data >= other.Data; }
    };

    template <typename TValue, typename TIterator = Iterator<TValue>, typename TConstIterator = Iterator<const TValue>>
    class Iterable
    {
      public:
        virtual TIterator begin() = 0;
        virtual TConstIterator begin() const = 0;

        virtual TIterator end() = 0;
        virtual TConstIterator end() const = 0;

        constexpr TIterator Begin() { return begin(); }
        constexpr TConstIterator Begin() const { return begin(); }

        constexpr TIterator End() { return end(); }
        constexpr TConstIterator End() const { return end(); }

      public:
        constexpr bool IsEmpty() const { return begin() == end(); }

        constexpr TValue* Data() { return &*begin(); }
        constexpr const TValue* Data() const { return &*begin(); }

        constexpr TValue& First() { return *begin(); }
        constexpr const TValue& First() const { return *begin(); }

        constexpr TValue& Last() { return *(end() -= 1); }
        constexpr const TValue& Last() const { return *(end() -= 1); }

        constexpr TValue& At(usz index) { return *(begin() += index); }
        constexpr const TValue& At(usz index) const { return *(begin() += index); }

        constexpr TValue& operator[](usz index) { return At(index); }
        constexpr const TValue& operator[](usz index) const { return At(index); }

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
