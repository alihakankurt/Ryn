#if RYN_PLATFORM_MACOS || RYN_PLATFORM_LINUX

#include <Ryn/Native/Platform.hpp>

#include <unistd.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <sys/time.h>

namespace Ryn
{
    Platform::Module Platform::LoadModule(const char* path)
    {
        return dlopen(path, RTLD_LAZY);
    }

    void Platform::FreeModule(Platform::Module handle)
    {
        dlclose(handle);
    }

    void* Platform::LoadFunction(void* handle, const char* name)
    {
        return dlsym(handle, name);
    }

    u64 Platform::GetTime()
    {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        return As<u64>(tv.tv_sec * 1'000'000 + tv.tv_usec);
    }

    bool Platform::WriteConsole(const char* value, usize length)
    {
        isize result = write(STDOUT_FILENO, value, length);
        return result >= 0 && As<usize>(result) == length;
    }

    usize Platform::ReadFile(const char* path, char*& out)
    {
        int fd = open(path, O_RDONLY);
        if (fd == -1)
            return 0;

        usize size = As<usize>(lseek(fd, 0, SEEK_END));
        lseek(fd, 0, SEEK_SET);

        out = new char[size + 1];
        read(fd, out, size);
        out[size] = '\0';

        close(fd);

        return size;
    }

    bool Platform::WriteFile(const char* path, const char* in, usize length)
    {
        int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1)
            return false;

        isize result = write(fd, in, length);
        close(fd);

        return result >= 0 && As<usize>(result) == length;
    }
}

#endif