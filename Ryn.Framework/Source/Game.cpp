#include <Ryn/Framework/Game.hpp>

namespace Ryn::Framework
{
    void Game::Run()
    {
        Windowing::WindowSettings settings;
        Configure(settings);

        Window = Windowing::Window::Create(settings);

        Initialize();

        while (Window->IsRunning())
        {
            Window->Update();
        }

        Finalize();

        delete Window;
    }
}
