#include <Ryn/IO/File.hpp>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace Ryn
{
    String File::Read(const Span<const char> path)
    {
        int file = open(path.Data(), O_RDONLY);
        if (file == -1)
        {
            return String{};
        }

        struct stat fileStats;
        if (fstat(file, &fileStats) == -1)
        {
            close(file);
            return String{};
        }

        usz fileSize = static_cast<usz>(fileStats.st_size);
        char* buffer = Memory::Allocate<char>(fileSize + 1);

        usz bytesReadTotal = 0;
        while (bytesReadTotal < fileSize)
        {
            ssize_t bytesRead = read(file, buffer + bytesReadTotal, fileSize - bytesReadTotal);
            if (bytesRead == -1)
            {
                Memory::Free<char>(buffer, fileSize + 1);
                return String{};
            }

            bytesReadTotal += static_cast<usz>(bytesRead);
        }

        close(file);
        buffer[fileSize] = '\0';

        return String{buffer, fileSize};
    }

    static bool WriteToFile(int file, const Span<const char> content)
    {
        usz bytesWrittenTotal = 0;
        while (bytesWrittenTotal < content.Length())
        {
            ssize_t bytesWritten = write(file, &content[bytesWrittenTotal], content.Length() - bytesWrittenTotal);
            if (bytesWritten == -1)
            {
                return false;
            }

            bytesWrittenTotal += static_cast<usz>(bytesWritten);
        }

        return true;
    }

    bool File::Write(const Span<const char> path, const Span<const char> content)
    {
        int file = open(path.Data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (file == -1)
        {
            return false;
        }

        bool isWritten = WriteToFile(file, content);
        close(file);
        return isWritten;
    }

    bool File::Append(const Span<const char> path, const Span<const char> content)
    {
        int file = open(path.Data(), O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (file == -1)
        {
            return false;
        }

        bool isWritten = WriteToFile(file, content);
        close(file);
        return isWritten;
    }

    bool File::Exists(const Span<const char> path)
    {
        return access(path.Data(), F_OK) != -1;
    }

    bool File::Delete(const Span<const char> path)
    {
        return unlink(path.Data()) != -1;
    }
}
