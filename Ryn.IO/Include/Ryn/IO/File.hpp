#pragma once

#include <Ryn/Core.hpp>

namespace Ryn::IO
{
    enum class FileMode
    {
        Read,
        Write,
        Append,
        ReadWrite
    };

    enum class SeekOrigin
    {
        Begin,
        Current,
        End
    };

    class File
    {
      private:
        struct FileInfo* _info;

      private:
        explicit File(FileInfo* info);

      public:
        ~File();

        File(const File& other) = delete;
        File(File&& other) noexcept;

        File& operator=(const File& other) = delete;
        File& operator=(File&& other) noexcept;

        static File Open(const Core::String& path, FileMode mode);
        static bool Exists(const Core::String& path);
        static bool Delete(const Core::String& path);

      public:
        bool Close();
        bool Read(Core::String& content);
        bool Write(const Core::String& content);
        bool Seek(Core::isz offset, SeekOrigin origin);

      public:
        static File StandardInput();
        static File StandardOutput();
        static File StandardError();
    };
}
