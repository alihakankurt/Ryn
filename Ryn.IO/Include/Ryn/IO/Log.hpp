#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Traits.hpp>
#include <Ryn/Core/Span.hpp>
#include <Ryn/Core/String.hpp>

namespace Ryn
{
    class Log
    {
      public:
        template <typename TValue>
        struct Writer
        {
            static void Write(const TValue& value) = delete;
        };

        template <>
        struct Writer<char>
        {
            static void Write(char value) { Log::Write(Span<const char>{1, &value}); }
        };

        template <u32 N>
        struct Writer<char[N]>
        {
            static void Write(const char (&value)[N]) { Log::Write(Span<const char>{N - 1, value}); }
        };

        template <>
        struct Writer<const char*>
        {
            static void Write(const char* value) { Log::Write(Span<const char>{String::Length(value), value}); }
        };

        template <>
        struct Writer<String>
        {
            static void Write(const String& value) { Log::Write(value); }
        };

        template <>
        struct Writer<Span<const char>>
        {
            static void Write(const Span<const char> value) { Log::Write(value); }
        };

        template <>
        struct Writer<bool>
        {
            static void Write(bool value)
            {
                char buffer[String::MaxBoolLength];
                Span<char> span = String::Format(buffer, value);
                Log::Write(span);
            }
        };

        template <Traits::SignedInteger TSigned>
        struct Writer<TSigned>
        {
            static void Write(TSigned value)
            {
                char buffer[String::MaxIntLength];
                Span<char> span = String::Format(buffer, static_cast<i64>(value));
                Log::Write(span);
            }
        };

        template <Traits::UnsignedInteger TUnsigned>
        struct Writer<TUnsigned>
        {
            static void Write(TUnsigned value)
            {
                char buffer[String::MaxIntLength];
                Span<char> span = String::Format(buffer, static_cast<u64>(value));
                Log::Write(span);
            }
        };

        template <Traits::FloatingPoint TFloat>
        struct Writer<TFloat>
        {
            static void Write(TFloat value)
            {
                char buffer[String::MaxFloatLength];
                Span<char> span = String::Format(buffer, static_cast<f64>(value));
                Log::Write(span);
            }
        };

      private:
        Log() = delete;
        ~Log() = delete;

#if RYN_DEBUG

      private:
        enum class Color
        {
            Reset,
            Black,
            Red,
            Green,
            Yellow,
            Blue,
            Magenta,
            Cyan,
            White
        };

        static void UseColor(Color color);

      private:
        static void Write(const Span<const char> span);

      public:
        template <typename... TArgs>
        static constexpr void Info(const TArgs&... args)
        {
            UseColor(Color::Green);
            Writer<char[8]>::Write("[INFO] ");
            UseColor(Color::Reset);
            (Writer<TArgs>::Write(args), ...);
            Writer<char>::Write('\n');
        }

        template <typename... TArgs>
        static constexpr void Warn(const TArgs&... args)
        {
            UseColor(Color::Yellow);
            Writer<char[8]>::Write("[WARN] ");
            UseColor(Color::Reset);
            (Writer<TArgs>::Write(args), ...);
            Writer<char>::Write('\n');
        }

        template <typename... TArgs>
        static constexpr void Error(const TArgs&... args)
        {
            UseColor(Color::Red);
            Writer<char[9]>::Write("[ERROR] ");
            UseColor(Color::Reset);
            (Writer<TArgs>::Write(args), ...);
            Writer<char>::Write('\n');
        }
#else

      private:
        static constexpr void Write(const Span<const char>) {}

      public:
        template <typename... TArgs>
        static constexpr void Info(const TArgs&...) {}

        template <typename... TArgs>
        static constexpr void Warn(const TArgs&...) {}

        template <typename... TArgs>
        static constexpr void Error(const TArgs&...) {}
#endif
    };
}
