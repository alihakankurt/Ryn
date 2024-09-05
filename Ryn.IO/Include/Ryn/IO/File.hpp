#pragma once

#include <Ryn/Core/Span.hpp>
#include <Ryn/Core/String.hpp>

namespace Ryn
{
    class File
    {
      public:
        File() = delete;
        ~File() = delete;

        static String Read(const Span<const char> path);
        static bool Write(const Span<const char> path, const Span<const char> content);
        static bool Append(const Span<const char> path, const Span<const char> content);
        static bool Exists(const Span<const char> path);
        static bool Delete(const Span<const char> path);
    };
}
