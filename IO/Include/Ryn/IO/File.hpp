#ifndef __RYN_IO_FILE_HPP__
#define __RYN_IO_FILE_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    class File
    {
      public:
        static String Read(const String& path);
        static bool Write(const String& path, const String& content);
    };
}

#endif