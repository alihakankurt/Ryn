#include <Ryn/IO/File.hpp>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace Ryn
{
    String File::Read(const Span<const char> path)
    {
        int file = open(&path[0], O_RDONLY);
        if (file == -1)
        {
            return String{};
        }

        struct stat fileStat;
        if (fstat(file, &fileStat) == -1)
        {
            close(file);
            return String{};
        }

        u32 fileSize = static_cast<u32>(fileStat.st_size);
        char* buffer = new char[fileSize];

        u32 bytesReadTotal = 0;
        while (bytesReadTotal < fileSize)
        {
            ssize_t bytesRead = read(file, buffer + bytesReadTotal, fileSize - bytesReadTotal);
            if (bytesRead == -1)
            {
                delete[] buffer;
                return String{};
            }

            bytesReadTotal += static_cast<u32>(bytesRead);
        }

        close(file);
        return String{buffer, fileSize};
    }

    static bool WriteToFile(int file, const Span<const char> content)
    {
        u32 bytesWrittenTotal = 0;
        while (bytesWrittenTotal < content.Length())
        {
            ssize_t bytesWritten = write(file, &content[bytesWrittenTotal], content.Length() - bytesWrittenTotal);
            if (bytesWritten == -1)
                return false;

            bytesWrittenTotal += static_cast<u32>(bytesWritten);
        }

        return true;
    }

    bool File::Write(const Span<const char> path, const Span<const char> content)
    {
        int file = open(&path[0], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (file == -1)
        {
            return false;
        }

        bool result = WriteToFile(file, content);
        close(file);
        return result;
    }

    bool File::Append(const Span<const char> path, const Span<const char> content)
    {
        int file = open(&path[0], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (file == -1)
        {
            return false;
        }

        bool result = WriteToFile(file, content);
        close(file);
        return result;
    }

    bool File::Exists(const Span<const char> path)
    {
        return access(&path[0], F_OK) != -1;
    }

    bool File::Delete(const Span<const char> path)
    {
        return unlink(&path[0]) != -1;
    }
}
