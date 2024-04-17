#ifndef __RYN_COLLECTIONS_LIST_HPP__
#define __RYN_COLLECTIONS_LIST_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    template <typename T>
    class List
    {
      private:
        static constexpr usize DefaultCapacity = 4;

      private:
        T* _data;
        usize _count;
        usize _capacity;

      public:
        List(usize capacity = 0)
        {
            _data = (capacity > 0) ? new T[capacity] : nullptr;
            _count = 0;
            _capacity = capacity;
        }

        List(const List& other)
        {
            _data = new T[other._capacity];
            _count = other._count;
            _capacity = other._capacity;

            for (usize i = 0; i < _count; i += 1)
                _data[i] = other._data[i];
        }

        List& operator=(const List& other)
        {
            if (this == &other)
                return *this;

            delete[] _data;

            _data = new T[other._capacity];
            _count = other._count;
            _capacity = other._capacity;

            for (usize i = 0; i < _count; i += 1)
                _data[i] = other._data[i];

            return *this;
        }

        List(List&& other)
        {
            _data = other._data;
            _count = other._count;
            _capacity = other._capacity;

            other._data = nullptr;
            other._count = 0;
            other._capacity = 0;
        }

        List& operator=(List&& other)
        {
            if (this == &other)
                return *this;

            delete[] _data;

            _data = other._data;
            _count = other._count;
            _capacity = other._capacity;

            other._data = nullptr;
            other._count = 0;
            other._capacity = 0;

            return *this;
        }

        ~List()
        {
            delete[] _data;
        }

        usize Count() const
        {
            return _count;
        }

        T& operator[](usize index)
        {
            return _data[index];
        }

        void Add(T&& item)
        {
            if (_count >= _capacity)
                Resize(_capacity << 1);

            _data[_count] = item;
            _count += 1;
        }

        void Insert(usize index, T&& item)
        {
            if (index > _count)
                return;

            if (_count >= _capacity)
                Resize(_capacity << 1);

            for (usize i = _count; i > index; i -= 1)
                _data[i] = _data[i - 1];

            _data[index] = item;
            _count += 1;
        }

        bool Remove(const T& item)
        {
            for (usize i = 0; i < _count; i += 1)
                if (_data[i] == item)
                    return RemoveAt(i);

            return false;
        }

        bool RemoveAt(usize index)
        {
            if (index >= _count)
                return false;

            for (usize i = index; i < _count - 1; i += 1)
                _data[i] = _data[i + 1];

            _count -= 1;
            return true;
        }

        void Clear()
        {
            _count = 0;
        }

      private:
        void Resize(usize newCapacity)
        {
            newCapacity = (newCapacity > 0) ? newCapacity : DefaultCapacity;
            T* newData = new T[newCapacity];
            for (usize i = 0; i < _count; i += 1)
                newData[i] = _data[i];

            delete[] _data;
            _data = newData;
            _capacity = newCapacity;
        }
    };
}

#endif