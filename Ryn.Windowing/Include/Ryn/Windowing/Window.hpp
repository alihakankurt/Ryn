#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Windowing/Input/InputContext.hpp>

namespace Ryn::Windowing
{
    struct WindowSettings
    {
        Core::u16 Width;
        Core::u16 Height;
        const char* Title;
    };

    class Window
    {
      public:
        Input::InputContext* Input;

      protected:
        Window() { Input = new Input::InputContext(); }

      public:
        virtual ~Window() { delete Input; }

        virtual bool IsRunning() const = 0;

        virtual void Close() = 0;
        virtual void Update() = 0;

        static Window* Create(const WindowSettings& settings);
    };
}
