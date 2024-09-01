#include <Ryn/IO/File.hpp>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace Ryn::IO
{
    struct FileInfo
    {
        int fd;
        bool open;
        bool std;
    };

    File::File(FileInfo* info)
    {
        _info = info;
    }

    File::~File()
    {
        if (_info && !_info->std)
        {
            Close();
            delete _info;
        }
    }

    File::File(File&& other) noexcept
    {
        _info = other._info;
        other._info = nullptr;
    }

    File& File::operator=(File&& other) noexcept
    {
        if (this != &other)
        {
            delete _info;
            _info = other._info;
            other._info = nullptr;
        }

        return *this;
    }

    File File::Open(const Core::String& path, FileMode mode)
    {
        struct UnixFileMode
        {
            static constexpr int Get(FileMode mode)
            {
                switch (mode)
                {
                    case FileMode::Read:      return O_RDONLY;
                    case FileMode::Write:     return O_WRONLY | O_CREAT | O_TRUNC;
                    case FileMode::Append:    return O_WRONLY | O_CREAT | O_APPEND;
                    case FileMode::ReadWrite: return O_RDWR | O_CREAT;
                }
            }
        };

        int fd = open(path.Raw(), UnixFileMode::Get(mode), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1)
        {
            return File(nullptr);
        }

        auto info = new FileInfo{fd, true, false};
        return File(info);
    }

    bool File::Exists(const Core::String& path)
    {
        struct stat buffer;
        return stat(path.Raw(), &buffer) == 0;
    }

    bool File::Delete(const Core::String& path)
    {
        return unlink(path.Raw()) == 0;
    }

    bool File::Close()
    {
        if (_info && _info->open && !_info->std)
        {
            close(_info->fd);
            _info->open = false;
            return true;
        }

        return false;
    }

    bool File::Read(Core::String& content)
    {
        if (_info)
        {
            off_t offset = lseek(_info->fd, 0, SEEK_END);
            if (offset == -1)
            {
                return false;
            }

            lseek(_info->fd, 0, SEEK_SET);

            Core::usz size = static_cast<Core::usz>(offset);
            char* buffer = new char[size + 1];
            read(_info->fd, buffer, size);
            buffer[size] = '\0';

            content = Core::String(buffer, size);
            return true;
        }

        return false;
    }

    bool File::Write(const Core::String& content)
    {
        if (_info)
        {
            write(_info->fd, content.Raw(), content.Length());
            return true;
        }

        return false;
    }

    bool File::Seek(Core::isz offset, SeekOrigin origin)
    {
        if (_info)
        {
            struct UnixSeekOrigin
            {
                static constexpr int Get(SeekOrigin origin)
                {
                    switch (origin)
                    {
                        case SeekOrigin::Begin:   return SEEK_SET;
                        case SeekOrigin::Current: return SEEK_CUR;
                        case SeekOrigin::End:     return SEEK_END;
                    }
                }
            };

            return lseek(_info->fd, offset, UnixSeekOrigin::Get(origin)) != -1;
        }

        return false;
    }

    File File::StandardInput()
    {
        static FileInfo info{STDIN_FILENO, true, true};
        return File(&info);
    }

    File File::StandardOutput()
    {
        static FileInfo info{STDOUT_FILENO, true, true};
        return File(&info);
    }

    File File::StandardError()
    {
        static FileInfo info{STDERR_FILENO, true, true};
        return File(&info);
    }
}
