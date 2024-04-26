#ifndef __RYN_CORE_NUMERIC_HPP__
#define __RYN_CORE_NUMERIC_HPP__

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Concepts.hpp>

namespace Ryn
{
    template <Number TNumber>
    struct Numeric
    {
        static inline constexpr TNumber Zero = TNumber{};
        static inline constexpr TNumber One = TNumber{};
        static inline constexpr TNumber MinValue = TNumber{};
        static inline constexpr TNumber MaxValue = TNumber{};
        static inline constexpr TNumber Epsilon = TNumber{};
        static inline constexpr TNumber NaN = TNumber{};
        static inline constexpr TNumber NegativeInfinity = TNumber{};
        static inline constexpr TNumber PositiveInfinity = TNumber{};
        static inline constexpr TNumber E = TNumber{};
        static inline constexpr TNumber Pi = TNumber{};
        static inline constexpr TNumber HalfPi = TNumber{};
        static inline constexpr TNumber Tau = TNumber{};
        static inline constexpr TNumber DegreesPerRadians = TNumber{};
        static inline constexpr TNumber RadiansPerDegrees = TNumber{};
    };

    template <>
    struct Numeric<i8>
    {
        static inline constexpr i8 Zero = 0;
        static inline constexpr i8 One = 1;
        static inline constexpr i8 MinValue = -128;
        static inline constexpr i8 MaxValue = 127;
        static inline constexpr i8 Epsilon = 0;
        static inline constexpr i8 NaN = 0;
        static inline constexpr i8 NegativeInfinity = 0;
        static inline constexpr i8 PositiveInfinity = 0;
        static inline constexpr i8 E = 2;
        static inline constexpr i8 Pi = 3;
        static inline constexpr i8 HalfPi = 1;
        static inline constexpr i8 Tau = 6;
        static inline constexpr i8 DegreesPerRadians = 57;
        static inline constexpr i8 RadiansPerDegrees = 0;
    };

    template <>
    struct Numeric<i16>
    {
        static inline constexpr i16 Zero = 0;
        static inline constexpr i16 One = 1;
        static inline constexpr i16 MinValue = -32'768;
        static inline constexpr i16 MaxValue = 32'767;
        static inline constexpr i16 Epsilon = 0;
        static inline constexpr i16 NaN = 0;
        static inline constexpr i16 NegativeInfinity = 0;
        static inline constexpr i16 PositiveInfinity = 0;
        static inline constexpr i16 E = 2;
        static inline constexpr i16 Pi = 3;
        static inline constexpr i16 HalfPi = 1;
        static inline constexpr i16 Tau = 6;
        static inline constexpr i16 DegreesPerRadians = 57;
        static inline constexpr i16 RadiansPerDegrees = 0;
    };

    template <>
    struct Numeric<i32>
    {
        static inline constexpr i32 Zero = 0;
        static inline constexpr i32 One = 1;
        static inline constexpr i32 MinValue = -2'147'483'648;
        static inline constexpr i32 MaxValue = 2'147'483'647;
        static inline constexpr i32 Epsilon = 0;
        static inline constexpr i32 NaN = 0;
        static inline constexpr i32 NegativeInfinity = 0;
        static inline constexpr i32 PositiveInfinity = 0;
        static inline constexpr i32 E = 2;
        static inline constexpr i32 Pi = 3;
        static inline constexpr i32 HalfPi = 1;
        static inline constexpr i32 Tau = 6;
        static inline constexpr i32 DegreesPerRadians = 57;
        static inline constexpr i32 RadiansPerDegrees = 0;
    };

    template <>
    struct Numeric<i64>
    {
        static inline constexpr i64 Zero = 0;
        static inline constexpr i64 One = 1;
        static inline constexpr i64 MinValue = -9'223'372'036'854'775'808;
        static inline constexpr i64 MaxValue = 9'223'372'036'854'775'807;
        static inline constexpr i64 Epsilon = 0;
        static inline constexpr i64 NaN = 0;
        static inline constexpr i64 NegativeInfinity = 0;
        static inline constexpr i64 PositiveInfinity = 0;
        static inline constexpr i64 E = 2;
        static inline constexpr i64 Pi = 3;
        static inline constexpr i64 HalfPi = 1;
        static inline constexpr i64 Tau = 6;
        static inline constexpr i64 DegreesPerRadians = 57;
        static inline constexpr i64 RadiansPerDegrees = 0;
    };

    template <>
    struct Numeric<isize>
    {
        static inline constexpr isize Zero = 0;
        static inline constexpr isize One = 1;
        static inline constexpr isize MinValue = -9'223'372'036'854'775'808;
        static inline constexpr isize MaxValue = 9'223'372'036'854'775'807;
        static inline constexpr isize Epsilon = 0;
        static inline constexpr isize NaN = 0;
        static inline constexpr isize NegativeInfinity = 0;
        static inline constexpr isize PositiveInfinity = 0;
        static inline constexpr isize E = 2;
        static inline constexpr isize Pi = 3;
        static inline constexpr isize HalfPi = 1;
        static inline constexpr isize Tau = 6;
        static inline constexpr isize DegreesPerRadians = 57;
        static inline constexpr isize RadiansPerDegrees = 0;
    };

    template <>
    struct Numeric<u8>
    {
        static inline constexpr u8 Zero = 0;
        static inline constexpr u8 One = 1;
        static inline constexpr u8 MinValue = 0;
        static inline constexpr u8 MaxValue = 255;
        static inline constexpr u8 Epsilon = 0;
        static inline constexpr u8 NaN = 0;
        static inline constexpr u8 NegativeInfinity = 0;
        static inline constexpr u8 PositiveInfinity = 0;
        static inline constexpr u8 E = 2;
        static inline constexpr u8 Pi = 3;
        static inline constexpr u8 HalfPi = 1;
        static inline constexpr u8 Tau = 6;
        static inline constexpr u8 DegreesPerRadians = 57;
        static inline constexpr u8 RadiansPerDegrees = 0;
    };

    template <>
    struct Numeric<u16>
    {
        static inline constexpr u16 Zero = 0;
        static inline constexpr u16 One = 1;
        static inline constexpr u16 MinValue = 0;
        static inline constexpr u16 MaxValue = 65'535;
        static inline constexpr u16 Epsilon = 0;
        static inline constexpr u16 NaN = 0;
        static inline constexpr u16 NegativeInfinity = 0;
        static inline constexpr u16 PositiveInfinity = 0;
        static inline constexpr u16 E = 2;
        static inline constexpr u16 Pi = 3;
        static inline constexpr u16 HalfPi = 1;
        static inline constexpr u16 Tau = 6;
        static inline constexpr u16 DegreesPerRadians = 57;
        static inline constexpr u16 RadiansPerDegrees = 0;
    };

    template <>
    struct Numeric<u32>
    {
        static inline constexpr u32 Zero = 0;
        static inline constexpr u32 One = 1;
        static inline constexpr u32 MinValue = 0;
        static inline constexpr u32 MaxValue = 4'294'967'295;
        static inline constexpr u32 Epsilon = 0;
        static inline constexpr u32 NaN = 0;
        static inline constexpr u32 NegativeInfinity = 0;
        static inline constexpr u32 PositiveInfinity = 0;
        static inline constexpr u32 E = 2;
        static inline constexpr u32 Pi = 3;
        static inline constexpr u32 HalfPi = 1;
        static inline constexpr u32 Tau = 6;
        static inline constexpr u32 DegreesPerRadians = 57;
        static inline constexpr u32 RadiansPerDegrees = 0;
    };

    template <>
    struct Numeric<u64>
    {
        static inline constexpr u64 Zero = 0;
        static inline constexpr u64 One = 1;
        static inline constexpr u64 MinValue = 0;
        static inline constexpr u64 MaxValue = 18'446'744'073'709'551'615;
        static inline constexpr u64 Epsilon = 0;
        static inline constexpr u64 NaN = 0;
        static inline constexpr u64 NegativeInfinity = 0;
        static inline constexpr u64 PositiveInfinity = 0;
        static inline constexpr u64 E = 2;
        static inline constexpr u64 Pi = 3;
        static inline constexpr u64 HalfPi = 1;
        static inline constexpr u64 Tau = 6;
        static inline constexpr u64 DegreesPerRadians = 57;
        static inline constexpr u64 RadiansPerDegrees = 0;
    };

    template <>
    struct Numeric<usize>
    {
        static inline constexpr usize Zero = 0;
        static inline constexpr usize One = 1;
        static inline constexpr usize MinValue = 0;
        static inline constexpr usize MaxValue = 18'446'744'073'709'551'615;
        static inline constexpr usize Epsilon = 0;
        static inline constexpr usize NaN = 0;
        static inline constexpr usize NegativeInfinity = 0;
        static inline constexpr usize PositiveInfinity = 0;
        static inline constexpr usize E = 2;
        static inline constexpr usize Pi = 3;
        static inline constexpr usize HalfPi = 1;
        static inline constexpr usize Tau = 6;
        static inline constexpr usize DegreesPerRadians = 57;
        static inline constexpr usize RadiansPerDegrees = 0;
    };

    template <>
    struct Numeric<f32>
    {
        static inline constexpr f32 Zero = 0.0f;
        static inline constexpr f32 One = 1.0f;
        static inline constexpr f32 MinValue = -3.402823466E+38f;
        static inline constexpr f32 MaxValue = 3.402823466E+38f;
        static inline constexpr f32 Epsilon = 1.192092896E-07f;
        static inline constexpr f32 NaN = 0x7FC0'0000;
        static inline constexpr f32 NegativeInfinity = 0xFF80'0000;
        static inline constexpr f32 PositiveInfinity = 0x7F80'0000;
        static inline constexpr f32 E = 2.71828182845904523536f;
        static inline constexpr f32 Pi = 3.14159265358979323846f;
        static inline constexpr f32 HalfPi = 1.57079632679489661923f;
        static inline constexpr f32 Tau = 6.28318530717958647692f;
        static inline constexpr f32 DegreesPerRadians = 57.2957795130823208768f;
        static inline constexpr f32 RadiansPerDegrees = 0.01745329251994329577f;
    };

    template <>
    struct Numeric<f64>
    {
        static inline constexpr f64 Zero = 0.0;
        static inline constexpr f64 One = 1.0;
        static inline constexpr f64 MinValue = -1.7976931348623158E+308;
        static inline constexpr f64 MaxValue = 1.7976931348623158E+308;
        static inline constexpr f64 Epsilon = 2.2204460492503131E-16;
        static inline constexpr f64 NaN = 0x7FF8'0000'0000'0000;
        static inline constexpr f64 NegativeInfinity = 0xFFF0'0000'0000'0000;
        static inline constexpr f64 PositiveInfinity = 0x7FF0'0000'0000'0000;
        static inline constexpr f64 E = 2.71828182845904523536;
        static inline constexpr f64 Pi = 3.14159265358979323846;
        static inline constexpr f64 HalfPi = 1.57079632679489661923;
        static inline constexpr f64 Tau = 6.28318530717958647692;
        static inline constexpr f64 DegreesPerRadians = 57.2957795130823208768;
        static inline constexpr f64 RadiansPerDegrees = 0.01745329251994329577;
    };
}

#endif