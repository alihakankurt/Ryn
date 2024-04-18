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
    concept SignedInteger = SignedIntegerTrait<TSelf>::Value;

    template <typename TSelf>
    concept UnsignedInteger = UnsignedIntegerTrait<TSelf>::Value;

    template <typename TSelf>
    concept Integer = IntegerTrait<TSelf>::Value;

    template <typename TSelf>
    concept FloatingPoint = FloatingPointTrait<TSelf>::Value;

    template <typename TSelf>
    concept SignedNumber = SignedNumberTrait<TSelf>::Value;

    template <typename TSelf>
    concept UnsignedNumber = UnsignedNumberTrait<TSelf>::Value;

    template <typename TSelf>
    concept Number = NumberTrait<TSelf>::Value;

    template <typename TSelf>
    using RemoveReference = typename ReferenceTrait<TSelf>::Type;

    template <typename TSelf>
    concept Reference = ReferenceTrait<TSelf>::Value;

    template <typename TSelf>
    using RemovePointer = typename PointerTrait<TSelf>::Type;

    template <typename TSelf>
    concept Pointer = PointerTrait<TSelf>::Value;

    template <typename TSelf>
    using RemoveConstant = typename ConstantTrait<TSelf>::Type;

    template <typename TSelf>
    concept Constant = ConstantTrait<TSelf>::Value;

    template <typename TSelf>
    concept Enum = EnumTrait<TSelf>::Value;

    template <typename TSelf>
    using UnderlyingType = typename UnderlyingTypeTrait<TSelf>::Type;

    template <typename TSelf>
    concept FunctionPointer = FunctionPointerTrait<TSelf>::Value;

    template <typename TSelf>
    concept PrimitiveType = PrimitiveTypeTrait<TSelf>::Value;

    template <typename TSelf>
    concept ValueType = ValueTypeTrait<TSelf>::Value;
}

#endif