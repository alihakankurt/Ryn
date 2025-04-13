#pragma once

namespace Ryn
{
    using i8 = signed char;
    using i16 = signed short;
    using i32 = signed int;
    using i64 = signed long long;
    
    using u8 = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned int;
    using u64 = unsigned long long;

    using isz = signed long;
    using usz = unsigned long;

    using f32 = float;
    using f64 = double;

    static_assert(sizeof(i8) == 1, "i8 is not 1 byte");
    static_assert(sizeof(i16) == 2, "i16 is not 2 bytes");
    static_assert(sizeof(i32) == 4, "i32 is not 4 bytes");
    static_assert(sizeof(i64) == 8, "i64 is not 8 bytes");
    
    static_assert(sizeof(u8) == 1, "u8 is not 1 byte");
    static_assert(sizeof(u16) == 2, "u16 is not 2 bytes");
    static_assert(sizeof(u32) == 4, "u32 is not 4 bytes");
    static_assert(sizeof(u64) == 8, "u64 is not 8 bytes");

    static_assert(sizeof(isz) == sizeof(void*), "isz is not the same size as a pointer");
    static_assert(sizeof(usz) == sizeof(void*), "usz is not the same size as a pointer");

    static_assert(sizeof(f32) == 4, "f32 is not 4 bytes");
    static_assert(sizeof(f64) == 8, "f64 is not 8 bytes");

    static constexpr i8 operator""_i8(unsigned long long value) { return static_cast<i8>(value); }
    static constexpr i16 operator""_i16(unsigned long long value) { return static_cast<i16>(value); }
    static constexpr i32 operator""_i32(unsigned long long value) { return static_cast<i32>(value); }
    static constexpr i64 operator""_i64(unsigned long long value) { return static_cast<i64>(value); }
    
    static constexpr u8 operator""_u8(unsigned long long value) { return static_cast<u8>(value); }
    static constexpr u16 operator""_u16(unsigned long long value) { return static_cast<u16>(value); }
    static constexpr u32 operator""_u32(unsigned long long value) { return static_cast<u32>(value); }
    static constexpr u64 operator""_u64(unsigned long long value) { return static_cast<u64>(value); }

    static constexpr isz operator""_isz(unsigned long long value) { return static_cast<isz>(value); }
    static constexpr usz operator""_usz(unsigned long long value) { return static_cast<usz>(value); }

    static constexpr f32 operator""_f32(unsigned long long value) { return static_cast<f32>(value); }
    static constexpr f64 operator""_f64(unsigned long long value) { return static_cast<f64>(value); }
    static constexpr f32 operator""_f32(long double value) { return static_cast<f32>(value); }
    static constexpr f64 operator""_f64(long double value) { return static_cast<f64>(value); }
}
