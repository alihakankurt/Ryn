#include <Ryn/Framework/EntryPoint.hpp>

#include <Ryn/Framework/Game.hpp>
#include <Ryn/Native/OpenGL.hpp>
#include <Ryn/Native/GLFW.hpp>
#include <Ryn/IO/Console.hpp>

using namespace Ryn;

int main(int argc, const char* argv[])
{
    (void)argc;
    (void)argv;

    OpenGL::Load();
    GLFW::Load();

#ifdef RYN_DEBUG
    GLFW::SetErrorCallback([](GLFW::ErrorCode error, const char* description)
    {
        Console::Write("[DEBUG] GLFW Error (", +error, "): ", description);
    });
#endif

    GLFW::Initialize();

    auto game = Game::Create();
    game->Run();
    delete game;

    GLFW::Terminate();
    GLFW::Unload();
    OpenGL::Unload();
}
