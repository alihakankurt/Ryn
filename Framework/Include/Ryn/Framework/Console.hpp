#ifndef __RYN_FRAMEWORK_CONSOLE_HPP__
#define __RYN_FRAMEWORK_CONSOLE_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    struct Console
    {
        static bool Write(char value);
        static bool Write(cstring value);
        static bool Write(const string& value);

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
    };
}

#endif