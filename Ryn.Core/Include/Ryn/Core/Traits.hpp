#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Traits
{
    template <typename T1, typename T2>
    struct SameTrait
    {
        static constexpr bool Value = false;
    };

    template <typename T>
    struct SameTrait<T, T>
    {
        static constexpr bool Value = true;
    };

    template <typename T1, typename T2>
    concept Same = SameTrait<T1, T2>::Value;

    template <typename T, typename... Ts>
    struct OneOfTrait
    {
        static constexpr bool Value = (SameTrait<T, Ts>::Value || ...);
    };

    template <typename T, typename... Ts>
    concept OneOf = OneOfTrait<T, Ts...>::Value;

    template <typename T>
    struct SignedIntegerTrait
    {
        static constexpr bool Value = OneOfTrait<T, i8, i16, i32, i64>::Value;
    };

    template <typename T>
    concept SignedInteger = SignedIntegerTrait<T>::Value;

    template <typename T>
    struct UnsignedIntegerTrait
    {
        static constexpr bool Value = OneOfTrait<T, u8, u16, u32, u64>::Value;
    };

    template <typename T>
    concept UnsignedInteger = UnsignedIntegerTrait<T>::Value;

    template <typename T>
    struct IntegerTrait
    {
        static constexpr bool Value = SignedIntegerTrait<T>::Value || UnsignedIntegerTrait<T>::Value;
    };

    template <typename T>
    concept Integer = IntegerTrait<T>::Value;

    template <typename T>
    struct FloatingPointTrait
    {
        static constexpr bool Value = OneOfTrait<T, f32, f64>::Value;
    };

    template <typename T>
    concept FloatingPoint = FloatingPointTrait<T>::Value;

    template <typename T>
    struct NumberTrait
    {
        static constexpr bool Value = IntegerTrait<T>::Value || FloatingPointTrait<T>::Value;
    };

    template <typename T>
    concept Number = NumberTrait<T>::Value;

    template <typename T>
    struct RemoveReferenceTrait
    {
        using Type = T;
    };

    template <typename T>
    struct RemoveReferenceTrait<T&>
    {
        using Type = T;
    };

    template <typename T>
    struct RemoveReferenceTrait<T&&>
    {
        using Type = T;
    };

    template <typename T>
    using RemoveReference = typename RemoveReferenceTrait<T>::Type;

    template <typename T>
    concept Reference = !Same<T, RemoveReference<T>>;

    template <typename T>
    struct RemoveConstTrait
    {
        using Type = T;
    };

    template <typename T>
    struct RemoveConstTrait<const T>
    {
        using Type = T;
    };

    template <typename T>
    using RemoveConst = typename RemoveConstTrait<T>::Type;

    template <typename T>
    concept Const = !Same<T, RemoveConst<T>>;
}
