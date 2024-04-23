#include <Ryn/IO/File.hpp>
#include <Ryn/Native/Platform.hpp>

namespace Ryn
{
    String File::Read(const String& path)
    {
        char* out = nullptr;
        usize length = Platform::ReadFile(path.Data(), out);
        return String(out, length);
    }

    bool File::Write(const String& path, const String& content)
    {
        return Platform::WriteFile(path.Data(), content.Data(), content.Length());
    }
}
