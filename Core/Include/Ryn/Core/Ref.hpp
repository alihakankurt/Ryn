#ifndef __RYN_CORE_REF_HPP__
#define __RYN_CORE_REF_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    template <typename TValue>
    class Ref
    {
      public:
        TValue* _value;
        usize* _count;

      public:
        Ref()
        {
            _value = nullptr;
            _count = nullptr;
        }

        Ref(TValue* value)
        {
            _value = value;
            _count = new usize(1);
        }

        Ref(TValue* value, usize* count)
        {
            _value = value;
            _count = count;

            if (_count != nullptr)
                *_count += 1;
        }

        Ref(const Ref<TValue>& other)
        {
            _value = other._value;
            _count = other._count;

            if (_count != nullptr)
                *_count += 1;
        }

        Ref<TValue>& operator=(const Ref<TValue>& other)
        {
            if (this == &other)
                return *this;

            Release();

            _value = other._value;
            _count = other._count;

            if (_count != nullptr)
                *_count += 1;

            return *this;
        }

        Ref(Ref<TValue>&& other)
        {
            _value = other._value;
            _count = other._count;

            other._value = nullptr;
            other._count = nullptr;
        }

        Ref<TValue>& operator=(Ref<TValue>&& other)
        {
            if (this == &other)
                return *this;

            Release();

            _value = other._value;
            _count = other._count;

            other._value = nullptr;
            other._count = nullptr;

            return *this;
        }

        ~Ref()
        {
            Release();
        }

        void Release()
        {
            if (_count == nullptr)
                return;

            *_count -= 1;

            if (*_count == 0)
            {
                delete _count;
                delete _value;
            }

            _value = nullptr;
            _count = nullptr;
        }

        template <typename TOther>
        Ref<TOther> As() const
        {
            return Ref<TOther>{Ryn::As<TOther*>(_value), _count};
        }

        TValue* Get() const
        {
            return _value;
        }

        TValue* operator->() const
        {
            return _value;
        }

        TValue& operator*() const
        {
            return *_value;
        }

        operator bool() const
        {
            return _value;
        }

        bool operator==(const Ref<TValue>& other) const
        {
            return _value == other._value;
        }

        bool operator!=(const Ref<TValue>& other) const
        {
            return _value != other._value;
        }
    };
}

#endif