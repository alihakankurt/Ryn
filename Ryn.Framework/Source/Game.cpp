#include <Ryn/Framework/Game.hpp>

namespace Ryn
{
    void Game::Run()
    {
        WindowSettings settings;
        Configure(settings);

        Window = Window::Create(settings);

        Initialize();

        while (Window->IsRunning())
        {
            Window->Update();
        }

        Finalize();

        delete Window;
    }
}
