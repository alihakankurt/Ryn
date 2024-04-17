#ifndef __RYN_CORE_CONCEPTS_HPP__
#define __RYN_CORE_CONCEPTS_HPP__

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Traits.hpp>

namespace Ryn
{
    template <typename TSelf, typename TOther>
    concept Is = IsTrait<TSelf, TOther>::Value;

    template <typename TSelf, typename... TOthers>
    concept IsAny = IsAnyTrait<TSelf, TOthers...>::Value;

    template <typename TSelf>
    concept IsSignedInteger = SignedIntegerTrait<TSelf>::Value;

    template <typename TSelf>
    concept IsUnsignedInteger = UnsignedIntegerTrait<TSelf>::Value;

    template <typename TSelf>
    concept IsInteger = IntegerTrait<TSelf>::Value;

    template <typename TSelf>
    concept IsFloatingPoint = FloatingPointTrait<TSelf>::Value;

    template <typename TSelf>
    concept IsSignedNumber = SignedNumberTrait<TSelf>::Value;

    template <typename TSelf>
    concept IsUnsignedNumber = UnsignedNumberTrait<TSelf>::Value;

    template <typename TSelf>
    concept IsNumber = NumberTrait<TSelf>::Value;

    template <typename TSelf>
    using RemoveReference = typename ReferenceTrait<TSelf>::Type;

    template <typename TSelf>
    concept IsReference = IsAny<TSelf, RemoveReference<TSelf>&, RemoveReference<TSelf>&&>;

    template <typename TSelf>
    using RemovePointer = typename PointerTrait<TSelf>::Type;

    template <typename TSelf>
    concept IsPointer = Is<TSelf, RemovePointer<TSelf>*>;

    template <typename TSelf>
    using RemoveConst = typename ConstTrait<TSelf>::Type;

    template <typename TSelf>
    concept IsConst = Is<TSelf, const RemoveConst<TSelf>>;

    template <typename TSelf>
    concept IsEnum = EnumTrait<TSelf>::Value;

    template <typename TSelf>
    using UnderlyingType = typename UnderlyingTypeTrait<TSelf>::Type;

    template <typename TSelf>
    concept IsFunction = FunctionPointerTrait<TSelf>::Value;

    template <typename TSelf>
    concept IsValueType = IsValueTypeTrait<TSelf>::Value;
}

#endif