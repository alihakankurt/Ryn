#pragma once

#include <Ryn/Core/Traits.hpp>
#include <Ryn/Core/Utility.hpp>

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
            CallableBase* Clone() const override { return new Callable<TLambda>(_lambda); }
        };

        const CallableBase* _callable;

      public:
        constexpr Function() :
            _callable{} {}

        template <typename TLambda>
        constexpr Function(TLambda lambda) :
            _callable{new Callable<TLambda>{lambda}} {}

        constexpr Function(const Function& other) :
            _callable{}
        {
            if (other._callable)
            {
                _callable = other._callable->Clone();
            }
        }

        constexpr Function(Function&& other) :
            _callable{Utility::Exchange(other._callable)} {}

        constexpr ~Function()
        {
            delete _callable;
            _callable = {};
        }

        constexpr Function& operator=(const Function& other)
        {
            if (this != &other)
            {
                delete _callable;
                _callable = {};
                if (other._callable)
                {
                    _callable = other._callable->Clone();
                }
            }
            return *this;
        }

        constexpr Function& operator=(Function&& other)
        {
            if (this != &other)
            {
                delete _callable;
                _callable = Utility::Exchange(other._callable);
            }
            return *this;
        }

        constexpr operator bool() const { return _callable; }
        constexpr TReturn operator()(TArgs... args) const { return _callable->Call(args...); }
    };

    template <typename TLambda>
    Function(TLambda) -> Function<Traits::Lambda<TLambda>>;

    template <typename... Ts>
    using Predicate = Function<bool(const Ts&...)>;

    template <typename... Ts>
    using Action = Function<void(const Ts&...)>;
}
