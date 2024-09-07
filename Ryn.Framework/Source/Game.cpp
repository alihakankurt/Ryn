#include <Ryn/Framework/Game.hpp>
#include <Ryn/Windowing/Events/KeyEvent.hpp>
#include <Ryn/Windowing/Events/MouseEvent.hpp>

namespace Ryn
{
    void Game::Run()
    {
        WindowSettings settings;
        Configure(settings);

        Window = Window::Create(settings);
        Input = new InputContext();

        Window->SetEventCallback([this](Event& event) { OnEvent(event); });

        Initialize();

        while (Window->IsRunning())
        {
            Input->Update();
            Window::PollEvents();
        }

        Finalize();

        delete Input;
        delete Window;
    }

    void Game::OnEvent(Event& event)
    {
        switch (event.Kind)
        {
            case EventKind::Unknown:
            {
                break;
            }
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
