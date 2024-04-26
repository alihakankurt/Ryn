#ifndef __RYN_FRAMEWORK_CONSOLE_HPP__
#define __RYN_FRAMEWORK_CONSOLE_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    class Console
    {
      private:
        static constexpr usize BufferSize = 64;
        static char Buffer[BufferSize];

      public:
        static bool Write(char value);
        static bool Write(const char* value);
        static bool Write(const string& value);

        static bool Write(bool value);

        static bool Write(i8 value);
        static bool Write(i16 value);
        static bool Write(i32 value);
        static bool Write(i64 value);

        static bool Write(u8 value);
        static bool Write(u16 value);
        static bool Write(u32 value);
        static bool Write(u64 value);

        static bool Write(f32 value);
        static bool Write(f64 value);

        template <typename... Args>
        static bool Write(Args... args)
        {
            return (Write(args) && ...);
        }

      private:
        static usize WriteInteger(u64 value, usize index, isize padding = 0);
        static usize WriteSign(bool negative, usize index);
    };
}

#endif