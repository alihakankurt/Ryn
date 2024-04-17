#include <Ryn/Framework/Game.hpp>

namespace Ryn
{
    void Game::Run()
    {
        WindowConfig windowConfig = {};
        Initialize(windowConfig);

        Window = Window::Create(windowConfig);
        Renderer = Renderer::Create();

        Window->IsActive();

        while (Window->IsActive())
        {
            Window->Update();
            Update();
            Render();
        }

        delete Renderer;
        delete Window;

        Finalize();
    }
}
