#pragma once

#include <Ryn/Core/Span.hpp>
#include <Ryn/Core/String.hpp>

namespace Ryn::IO
{
    class File
    {
      public:
        File() = delete;
        ~File() = delete;

        static Core::String Read(const Core::Span<const char> path);
        static bool Write(const Core::Span<const char> path, const Core::Span<const char> content);
        static bool Append(const Core::Span<const char> path, const Core::Span<const char> content);
        static bool Exists(const Core::Span<const char> path);
        static bool Delete(const Core::Span<const char> path);
    };
}
