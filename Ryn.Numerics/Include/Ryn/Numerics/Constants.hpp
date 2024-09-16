#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Traits.hpp>

namespace Ryn
{
    template <Traits::Number TNumber>
    struct NumericConstants
    {
        static constexpr TNumber Zero{};
        static constexpr TNumber One{};
        static constexpr TNumber Min{};
        static constexpr TNumber Max{};
        static constexpr TNumber Epsilon{};
        static constexpr TNumber E{};
        static constexpr TNumber Pi{};
        static constexpr TNumber Phi{};
    };

    template <>
    struct NumericConstants<i8>
    {
        static constexpr i8 Zero = 0_i8;
        static constexpr i8 One = 1_i8;
        static constexpr i8 Min = -127_i8 - 1_i8;
        static constexpr i8 Max = 127_i8;
        static constexpr i8 Epsilon = 0_i8;
        static constexpr i8 E = 2_i8;
        static constexpr i8 Pi = 3_i8;
        static constexpr i8 Phi = 1_i8;
    };

    template <>
    struct NumericConstants<i16>
    {
        static constexpr i16 Zero = 0_i16;
        static constexpr i16 One = 1_i16;
        static constexpr i16 Min = -32'767_i16 - 1_i16;
        static constexpr i16 Max = 32'767_i16;
        static constexpr i16 Epsilon = 0_i16;
        static constexpr i16 E = 2_i16;
        static constexpr i16 Pi = 3_i16;
        static constexpr i16 Phi = 1_i16;
    };

    template <>
    struct NumericConstants<i32>
    {
        static constexpr i32 Zero = 0_i32;
        static constexpr i32 One = 1_i32;
        static constexpr i32 Min = -2'147'483'647_i32 - 1_i32;
        static constexpr i32 Max = 2'147'483'647_i32;
        static constexpr i32 Epsilon = 0_i32;
        static constexpr i32 E = 2_i32;
        static constexpr i32 Pi = 3_i32;
        static constexpr i32 Phi = 1_i32;
    };

    template <>
    struct NumericConstants<i64>
    {
        static constexpr i64 Zero = 0_i64;
        static constexpr i64 One = 1_i64;
        static constexpr i64 Min = -9'223'372'036'854'775'807_i64 - 1_i64;
        static constexpr i64 Max = 9'223'372'036'854'775'807_i64;
        static constexpr i64 Epsilon = 0_i64;
        static constexpr i64 E = 2_i64;
        static constexpr i64 Pi = 3_i64;
        static constexpr i64 Phi = 1_i64;
    };

    template <>
    struct NumericConstants<u8>
    {
        static constexpr u8 Zero = 0_u8;
        static constexpr u8 One = 1_u8;
        static constexpr u8 Min = 0_u8;
        static constexpr u8 Max = 255_u8;
        static constexpr u8 Epsilon = 0_u8;
        static constexpr u8 E = 2_u8;
        static constexpr u8 Pi = 3_u8;
        static constexpr u8 Phi = 1_u8;
    };

    template <>
    struct NumericConstants<u16>
    {
        static constexpr u16 Zero = 0_u16;
        static constexpr u16 One = 1_u16;
        static constexpr u16 Min = 0_u16;
        static constexpr u16 Max = 65'535_u16;
        static constexpr u16 Epsilon = 0_u16;
        static constexpr u16 E = 2_u16;
        static constexpr u16 Pi = 3_u16;
        static constexpr u16 Phi = 1_u16;
    };

    template <>
    struct NumericConstants<u32>
    {
        static constexpr u32 Zero = 0_u32;
        static constexpr u32 One = 1_u32;
        static constexpr u32 Min = 0_u32;
        static constexpr u32 Max = 4'294'967'295_u32;
        static constexpr u32 Epsilon = 0_u32;
        static constexpr u32 E = 2_u32;
        static constexpr u32 Pi = 3_u32;
        static constexpr u32 Phi = 1_u32;
    };

    template <>
    struct NumericConstants<u64>
    {
        static constexpr u64 Zero = 0_u64;
        static constexpr u64 One = 1_u64;
        static constexpr u64 Min = 0_u64;
        static constexpr u64 Max = 18'446'744'073'709'551'615_u64;
        static constexpr u64 Epsilon = 0_u64;
        static constexpr u64 E = 2_u64;
        static constexpr u64 Pi = 3_u64;
        static constexpr u64 Phi = 1_u64;
    };

    template <>
    struct NumericConstants<f32>
    {
        static constexpr f32 Zero = 0_f32;
        static constexpr f32 One = 1_f32;
        static constexpr f32 Min = -3.402823466e+38_f32;
        static constexpr f32 Max = 3.402823466e+38_f32;
        static constexpr f32 Epsilon = 1.192092896e-07_f32;
        static constexpr f32 E = 2.71828182845904523536_f32;
        static constexpr f32 Pi = 3.14159265358979323846_f32;
        static constexpr f32 Phi = 1.61803398874989484820_f32;
    };

    template <>
    struct NumericConstants<f64>
    {
        static constexpr f64 Zero = 0_f64;
        static constexpr f64 One = 1_f64;
        static constexpr f64 Min = -1.79769313486231570815e+308_f64;
        static constexpr f64 Max = 1.79769313486231570815e+308_f64;
        static constexpr f64 Epsilon = 2.22044604925031308085e-16_f64;
        static constexpr f64 E = 2.71828182845904523536_f64;
        static constexpr f64 Pi = 3.14159265358979323846_f64;
        static constexpr f64 Phi = 1.61803398874989484820_f64;
    };
}
