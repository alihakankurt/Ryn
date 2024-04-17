#include <Ryn.hpp>
#include <Ryn/Native.hpp>

namespace Ryn
{
    void Initialize()
    {
        OpenGL::Load();

        GLFW::Load();
        GLFW::Initialize();
    }

    void Finalize()
    {
        GLFW::Terminate();
        GLFW::Unload();

        OpenGL::Unload();
    }
}