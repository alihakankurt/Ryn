#include <Ryn/IO/File.hpp>
#include <Ryn/Native/Platform.hpp>

namespace Ryn
{
    string File::Read(const string& path)
    {
        char* out = nullptr;
        usize length = Platform::ReadFile(path.Data(), out);
        return string(out, length);
    }

    bool File::Write(const string& path, const string& content)
    {
        return Platform::WriteFile(path.Data(), content.Data(), content.Length());
    }
}
