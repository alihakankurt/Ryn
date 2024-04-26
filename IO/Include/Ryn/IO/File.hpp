#ifndef __RYN_IO_FILE_HPP__
#define __RYN_IO_FILE_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    class File
    {
      public:
        static string Read(const string& path);
        static bool Write(const string& path, const string& content);
    };
}

#endif