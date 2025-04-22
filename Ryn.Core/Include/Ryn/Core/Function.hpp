#pragma once

#include <Ryn/Core/Traits.hpp>
#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Memory.hpp>

namespace Ryn
{
    template <typename TSignature>
    class Function;

    template <typename TReturn, typename... TArgs>
    class Function<TReturn(TArgs...)>
    {
      private:
        class CallableBase
        {
          public:
            virtual ~CallableBase() {}
            virtual TReturn Call(TArgs... args) const = 0;
            virtual CallableBase* Clone() const = 0;
        };

        template <typename TLambda>
        class Callable : public CallableBase
        {
          private:
            TLambda _lambda;

          public:
            explicit Callable(TLambda lambda) :
                _lambda(lambda) {}

            TReturn Call(TArgs... args) const override { return _lambda(args...); }
            CallableBase* Clone() const override { return Memory::Allocate<Callable<TLambda>>(_lambda); }
        };

        const CallableBase* _callable;

      public:
        constexpr Function() :
            _callable{} {}

        template <typename TLambda>
        Function(TLambda lambda) :
            _callable{Memory::Allocate<Callable<TLambda>>(lambda)} {}

        Function(const Function& other) :
            _callable{}
        {
            if (other._callable)
            {
                _callable = other._callable->Clone();
            }
        }

        constexpr Function(Function&& other) :
            _callable{Utility::Exchange(other._callable)} {}

        ~Function()
        {
            Memory::Free<CallableBase>(_callable);
            _callable = {};
        }

        Function& operator=(const Function& other)
        {
            if (this != &other)
            {
                Memory::Free<CallableBase>(_callable);
                _callable = {};
                if (other._callable)
                {
                    _callable = other._callable->Clone();
                }
            }
            return *this;
        }

        Function& operator=(Function&& other)
        {
            if (this != &other)
            {
                Memory::Free<CallableBase>(_callable);
                _callable = Utility::Exchange(other._callable);
            }
            return *this;
        }

        constexpr operator bool() const { return _callable; }
        constexpr TReturn operator()(TArgs... args) const { return _callable->Call(args...); }
    };

    template <typename TLambda>
    Function(TLambda) -> Function<Traits::Lambda<TLambda>>;

    template <typename... TArgs>
    using Predicate = Function<bool(const TArgs&...)>;

    template <typename... TArgs>
    using Action = Function<void(const TArgs&...)>;
}
