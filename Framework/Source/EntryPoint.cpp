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
    if (GLFW::Initialize == nullptr)
        Console::Write("GLFW::Initialize is null\n");

    GLFW::Initialize();

    auto game = Game::Create();
    game->Run();
    delete game;

    GLFW::Terminate();
    GLFW::Unload();
    OpenGL::Unload();
}
