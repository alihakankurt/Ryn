#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    class Time
    {
      private:
        f64 _seconds;

      public:
        constexpr Time() :
            _seconds{} {}

        constexpr explicit Time(f64 seconds) :
            _seconds(seconds) {}

        constexpr f64 Seconds() const { return _seconds; }

        constexpr operator f64() const { return _seconds; }

        constexpr Time operator+(const Time& other) const { return Time(_seconds + other._seconds); }
        constexpr Time operator-(const Time& other) const { return Time(_seconds - other._seconds); }

        constexpr bool operator==(const Time& other) const { return _seconds == other._seconds; }
        constexpr bool operator!=(const Time& other) const { return _seconds != other._seconds; }
        constexpr bool operator<(const Time& other) const { return _seconds < other._seconds; }
        constexpr bool operator>(const Time& other) const { return _seconds > other._seconds; }
        constexpr bool operator<=(const Time& other) const { return _seconds <= other._seconds; }
        constexpr bool operator>=(const Time& other) const { return _seconds >= other._seconds; }
    };

    class Clock
    {
      private:
        Time _start;
        Time _cycle;

      public:
        inline Clock() :
            _start(Now()),
            _cycle(_start) {}

        inline void Restart() { _cycle = Clock::Now(); }

        inline Time Total() const { return Clock::Now() - _start; }
        inline Time Delta() const { return Clock::Now() - _cycle; }

      public:
        static Time Now();
    };
}
