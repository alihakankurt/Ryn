#include <Ryn/Framework/Game.hpp>
#include <Ryn/Windowing/Events/KeyEvent.hpp>
#include <Ryn/Windowing/Events/MouseEvent.hpp>
#include <Ryn/IO/Log.hpp>

namespace Ryn
{
    void Game::Run()
    {
        WindowSettings settings;
        Configure(settings);

        Input = new InputContext();
        Window = Window::Create(settings);
        Renderer = Renderer::Create(*Window);

        Window->SetEventCallback([this](Event& event) { OnEvent(event); });

        Initialize();

        while (Window->IsRunning())
        {
            Input->Update();
            Window::PollEvents();
        }

        Finalize();

        delete Renderer;
        delete Window;
        delete Input;
    }

    void Game::OnEvent(Event& event)
    {
        switch (event.Kind)
        {
            case EventKind::WindowClose:
            {
                break;
            }
            case EventKind::WindowMove:
            {
                break;
            }
            case EventKind::WindowResize:
            {
                break;
            }
            case EventKind::WindowFocus:
            {
                break;
            }
            case EventKind::WindowLostFocus:
            {
                break;
            }
            case EventKind::KeyPress:
            {
                KeyPressEvent& keyPressEvent = event.As<KeyPressEvent>();
                Input->SetKeyState(keyPressEvent.Key, KeyState::Pressed);
                break;
            }
            case EventKind::KeyRelease:
            {
                KeyReleaseEvent& keyReleaseEvent = event.As<KeyReleaseEvent>();
                Input->SetKeyState(keyReleaseEvent.Key, KeyState::Released);
                break;
            }
            case EventKind::MouseMove:
            {
                MouseMoveEvent& mouseMoveEvent = event.As<MouseMoveEvent>();
                Input->SetMousePosition(mouseMoveEvent.Position);
                break;
            }
            case EventKind::MouseScroll:
            {
                break;
            }
            case EventKind::MouseButtonPress:
            {
                MouseButtonPressEvent& mouseButtonPressEvent = event.As<MouseButtonPressEvent>();
                Input->SetMouseButtonState(mouseButtonPressEvent.Button, MouseButtonState::Pressed);
                break;
            }
            case EventKind::MouseButtonRelease:
            {
                MouseButtonReleaseEvent& mouseButtonReleaseEvent = event.As<MouseButtonReleaseEvent>();
                Input->SetMouseButtonState(mouseButtonReleaseEvent.Button, MouseButtonState::Released);
                break;
            }
        }
    }
}
