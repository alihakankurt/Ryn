#ifndef __RYN_COLLECTIONS_LIST_HPP__
#define __RYN_COLLECTIONS_LIST_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    template <typename TItem>
    class List
    {
      private:
        static constexpr usize DefaultCapacity = 4;

      private:
        TItem* _data;
        usize _count;
        usize _capacity;

      public:
        inline constexpr List(usize capacity = 0)
        {
            _data = (capacity > 0) ? new TItem[capacity] : nullptr;
            _count = 0;
            _capacity = capacity;
        }

        List(const List& other)
        {
            _data = new TItem[other._capacity];
            _count = other._count;
            _capacity = other._capacity;
            Memory::Copy(_data, other._data, _count);
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

        ~List()
        {
            delete[] _data;
        }

        List& operator=(const List& other)
        {
            if (this == &other)
                return *this;

            delete[] _data;

            _data = new TItem[other._capacity];
            _count = other._count;
            _capacity = other._capacity;
            Memory::Copy(_data, other._data, _count);

            return *this;
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

        inline TItem& operator[](usize index)
        {
            return _data[index];
        }

        inline const TItem& operator[](usize index) const
        {
            return _data[index];
        }

        inline TItem* Begin()
        {
            return (_count > 0) ? _data : nullptr;
        }

        inline const TItem* Begin() const
        {
            return (_count > 0) ? _data : nullptr;
        }

        inline TItem* End()
        {
            return (_count > 0) ? _data + _count : nullptr;
        }

        inline const TItem* End() const
        {
            return (_count > 0) ? _data + _count : nullptr;
        }

        inline usize Count() const
        {
            return _count;
        }

        void Add(const TItem& item)
        {
            if (_count >= _capacity)
                Resize(_capacity << 1);

            _data[_count] = item;
            _count += 1;
        }

        void Add(TItem&& item)
        {
            if (_count >= _capacity)
                Resize(_capacity << 1);

            _data[_count] = item;
            _count += 1;
        }

        void Insert(usize index, const TItem& item)
        {
            if (index > _count)
                return;

            if (_count >= _capacity)
                Resize(_capacity << 1);

            Memory::Shift(_data + index, _count - index, 1);
            _data[index] = item;
            _count += 1;
        }

        void Insert(usize index, TItem&& item)
        {
            if (index > _count)
                return;

            if (_count >= _capacity)
                Resize(_capacity << 1);

            Memory::Shift(_data + index, _count - index, 1);
            _data[index] = item;
            _count += 1;
        }

        bool Remove(const TItem& item)
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

            Memory::Shift(_data + index + 1, _count - index - 1, -1);
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
            _capacity = (newCapacity > 0) ? newCapacity : DefaultCapacity;
            TItem* newData = new TItem[_capacity];
            Memory::Copy(newData, _data, _count);
            delete[] _data;
            _data = newData;
        }
    };
}

#endif