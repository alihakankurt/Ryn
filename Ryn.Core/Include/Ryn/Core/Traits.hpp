#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Traits
{
    template <typename T0, typename T1>
    struct SameTrait
    {
        static constexpr bool Value = false;
    };

    template <typename T>
    struct SameTrait<T, T>
    {
        static constexpr bool Value = true;
    };

    template <typename T0, typename T1>
    concept Same = SameTrait<T0, T1>::Value;

    template <typename T, typename... Ts>
    struct OneOfTrait
    {
        static constexpr bool Value = (SameTrait<T, Ts>::Value || ...);
    };

    template <typename T, typename... Ts>
    concept OneOf = OneOfTrait<T, Ts...>::Value;

    template <typename T>
    struct ReferenceTrait
    {
        static constexpr bool Value = false;
        using Type = T;
    };

    template <typename T>
    struct ReferenceTrait<T&>
    {
        static constexpr bool Value = true;
        using Type = T;
    };

    template <typename T>
    struct ReferenceTrait<T&&>
    {
        static constexpr bool Value = true;
        using Type = T;
    };

    template <typename T>
    concept Reference = ReferenceTrait<T>::Value;

    template <typename T>
    using RemoveReference = typename ReferenceTrait<T>::Type;

    template <typename T>
    struct ConstTrait
    {
        static constexpr bool Value = false;
        using Type = T;
    };

    template <typename T>
    struct ConstTrait<const T>
    {
        static constexpr bool Value = true;
        using Type = T;
    };

    template <typename T>
    struct ConstTrait<const volatile T>
    {
        static constexpr bool Value = true;
        using Type = volatile T;
    };

    template <typename T>
    concept Const = ConstTrait<T>::Value;

    template <typename T>
    using RemoveConst = typename ConstTrait<T>::Type;

    template <typename T>
    struct VolatileTrait
    {
        static constexpr bool Value = false;
        using Type = T;
    };

    template <typename T>
    struct VolatileTrait<volatile T>
    {
        static constexpr bool Value = true;
        using Type = T;
    };

    template <typename T>
    struct VolatileTrait<const volatile T>
    {
        static constexpr bool Value = true;
        using Type = const T;
    };

    template <typename T>
    concept Volatile = VolatileTrait<T>::Value;

    template <typename T>
    using RemoveVolatile = typename VolatileTrait<T>::Type;

    template <typename T>
    using RemoveConstVolatile = RemoveConst<RemoveVolatile<T>>;

    template <typename T>
    struct PointerTrait
    {
        static constexpr bool Value = false;
        using Type = T;
    };

    template <typename T>
    struct PointerTrait<T*>
    {
        static constexpr bool Value = true;
        using Type = T;
    };

    template <typename T>
    concept Pointer = PointerTrait<T>::Value;

    template <typename T>
    using RemovePointer = typename PointerTrait<T>::Type;

    template <typename T>
    struct VoidTrait
    {
        static constexpr bool Value = false;
        using Type = T;
    };

    template <>
    struct VoidTrait<void>
    {
        static constexpr bool Value = true;
        using Type = void;
    };

    template <typename T>
    concept Void = VoidTrait<T>::Value;

    template <typename T>
    struct SignedIntegerTrait
    {
        static constexpr bool Value = OneOfTrait<T, i8, i16, i32, i64, isz>::Value;
    };

    template <typename T>
    concept SignedInteger = SignedIntegerTrait<T>::Value;

    template <typename T>
    struct UnsignedIntegerTrait
    {
        static constexpr bool Value = OneOfTrait<T, u8, u16, u32, u64, usz>::Value;
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

    template <typename TLambda>
    struct LambdaTrait;

    template <typename TLambda, typename TReturn, typename... TArgs>
    struct LambdaTrait<TReturn (TLambda::*)(TArgs...) const>
    {
        using Type = TReturn(TArgs...);
    };

    template <typename TLambda>
    using Lambda = typename LambdaTrait<decltype(&TLambda::operator())>::Type;
}
