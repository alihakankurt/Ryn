#include <Ryn/Framework/Game.hpp>

namespace Ryn
{
    void Game::Run()
    {
        WindowConfig windowConfig = {};
        Configure(windowConfig);

        Window = Window::Create(windowConfig);
        Renderer = Renderer::Create();
        Initialize();

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
