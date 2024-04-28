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
        }

        Finalize();
        Renderer.Release();
        Input.Release();
        Window.Release();
    }
}
