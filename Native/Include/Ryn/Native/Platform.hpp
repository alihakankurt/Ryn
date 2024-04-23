#ifndef __RYN_NATIVE_PLATFORM_HPP__
#define __RYN_NATIVE_PLATFORM_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    class Platform
    {
      public:
        using Module = void*;

      public:
        static Module LoadModule(const char* path);

        static void FreeModule(Module handle);

        template <typename TFunction>
        static inline constexpr TFunction LoadFunction(Module handle, const char* name)
        {
            return As<TFunction>(LoadFunction(handle, name));
        }

      private:
        static void* LoadFunction(Module handle, const char* name);

      public:
        static u64 GetTime();

      public:
        static bool WriteConsole(const char* value, usize length);

        static usize ReadFile(const char* path, char*& out);
        static bool WriteFile(const char* path, const char* in, usize length);
    };
}

#endif