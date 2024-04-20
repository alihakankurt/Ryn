#include <Ryn/Framework/Game.hpp>

namespace Ryn
{
    void Game::Run()
    {
        WindowConfig windowConfig = {};
        Configure(windowConfig);

        Window = Window::Create(windowConfig);
        Input = Window->GetInputContext();
        Renderer = Renderer::Create();
        Initialize();

        while (Window->IsActive())
        {
            Window->Update();
            Update();
            Render();
            Window->Present();
        }

        delete Renderer;
        delete Window;
        Finalize();
    }
}
