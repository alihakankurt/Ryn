#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    class Time
    {
      public:
        static constexpr f64 NanosecondsPerSecond = 1e9_f64;

      private:
        f64 _nanoseconds;

      public:
        constexpr Time() :
            _nanoseconds{} {}

        constexpr explicit Time(f64 nanoseconds) :
            _nanoseconds(nanoseconds) {}

        constexpr f64 Seconds() const { return _nanoseconds / NanosecondsPerSecond; }

        constexpr operator f64() const { return _nanoseconds / NanosecondsPerSecond; }

        constexpr Time operator+(const Time& other) const { return Time(_nanoseconds + other._nanoseconds); }
        constexpr Time operator-(const Time& other) const { return Time(_nanoseconds - other._nanoseconds); }

        constexpr bool operator==(const Time& other) const { return _nanoseconds == other._nanoseconds; }
        constexpr bool operator!=(const Time& other) const { return _nanoseconds != other._nanoseconds; }
        constexpr bool operator<(const Time& other) const { return _nanoseconds < other._nanoseconds; }
        constexpr bool operator>(const Time& other) const { return _nanoseconds > other._nanoseconds; }
        constexpr bool operator<=(const Time& other) const { return _nanoseconds <= other._nanoseconds; }
        constexpr bool operator>=(const Time& other) const { return _nanoseconds >= other._nanoseconds; }
    };

    class Clock
    {
      private:
        Time _start;
        Time _cycle;

      public:
        Clock() :
            _start(Now()),
            _cycle(_start) {}

        void Restart() { _cycle = Clock::Now(); }

        Time Total() const { return Clock::Now() - _start; }
        Time Delta() const { return Clock::Now() - _cycle; }

      public:
        static Time Now();
    };
}
