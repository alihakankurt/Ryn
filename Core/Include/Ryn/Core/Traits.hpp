#ifndef __RYN_CORE_TRAITS_HPP__
#define __RYN_CORE_TRAITS_HPP__

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    template <typename TSelf, typename TOther>
    struct IsTrait
    {
        static constexpr bool Value = false;
    };

    template <typename TSelf>
    struct IsTrait<TSelf, TSelf>
    {
        static constexpr bool Value = true;
    };

    template <typename TSelf, typename... TOthers>
    struct IsAnyTrait
    {
        static constexpr bool Value = (IsTrait<TSelf, TOthers>::Value || ...);
    };

    template <typename TSelf>
    struct SignedIntegerTrait
    {
        static constexpr bool Value = IsAnyTrait<TSelf, i8, i16, i32, i64, isize>::Value;
    };

    template <typename TSelf>
    struct UnsignedIntegerTrait
    {
        static constexpr bool Value = IsAnyTrait<TSelf, u8, u16, u32, u64, usize>::Value;
    };

    template <typename TSelf>
    struct IntegerTrait
    {
        static constexpr bool Value = SignedIntegerTrait<TSelf>::Value || UnsignedIntegerTrait<TSelf>::Value;
    };

    template <typename TSelf>
    struct FloatingPointTrait
    {
        static constexpr bool Value = IsAnyTrait<TSelf, f32, f64>::Value;
    };

    template <typename TSelf>
    struct SignedNumberTrait
    {
        static constexpr bool Value = SignedIntegerTrait<TSelf>::Value || FloatingPointTrait<TSelf>::Value;
    };

    template <typename TSelf>
    struct UnsignedNumberTrait
    {
        static constexpr bool Value = UnsignedIntegerTrait<TSelf>::Value;
    };

    template <typename TSelf>
    struct NumberTrait
    {
        static constexpr bool Value = SignedNumberTrait<TSelf>::Value || UnsignedNumberTrait<TSelf>::Value;
    };

    template <typename TSelf>
    struct ReferenceTrait
    {
        using Type = TSelf;
        static constexpr bool Value = false;
    };

    template <typename TSelf>
    struct ReferenceTrait<TSelf&>
    {
        using Type = TSelf;
        static constexpr bool Value = true;
    };

    template <typename TSelf>
    struct ReferenceTrait<TSelf&&>
    {
        using Type = TSelf;
        static constexpr bool Value = true;
    };

    template <typename TSelf>
    struct PointerTrait
    {
        using Type = TSelf;
        static constexpr bool Value = false;
    };

    template <typename TSelf>
    struct PointerTrait<TSelf*>
    {
        using Type = TSelf;
        static constexpr bool Value = true;
    };

    template <typename TSelf>
    struct ConstantTrait
    {
        using Type = TSelf;
        static constexpr bool Value = false;
    };

    template <typename TSelf>
    struct ConstantTrait<const TSelf>
    {
        using Type = TSelf;
        static constexpr bool Value = true;
    };

    template <typename TSelf>
    struct EnumTrait
    {
        static constexpr bool Value = __is_enum(TSelf);
    };

    template <typename TSelf>
    struct UnderlyingTypeTrait
    {
        using Type = TSelf;
    };

    template <typename TSelf>
    requires EnumTrait<TSelf>::Value
    struct UnderlyingTypeTrait<TSelf>
    {
        using Type = __underlying_type(TSelf);
    };

    template <typename TSelf>
    struct FunctionPointerTrait
    {
        static constexpr bool Value = false;
    };

    template <typename TSelf, typename... TArgs>
    struct FunctionPointerTrait<TSelf (*)(TArgs...)>
    {
        static constexpr bool Value = true;
    };

    template <typename TSelf>
    struct PrimitiveTypeTrait
    {
        static constexpr bool Value = NumberTrait<TSelf>::Value || IsAnyTrait<TSelf, bool, char>::Value;
    };

    template <typename TSelf>
    struct ValueTypeTrait
    {
        static constexpr bool Value = PrimitiveTypeTrait<TSelf>::Value || PointerTrait<TSelf>::Value || EnumTrait<TSelf>::Value;
    };
}

#endif