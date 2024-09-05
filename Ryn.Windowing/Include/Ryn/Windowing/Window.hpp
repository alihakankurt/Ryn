#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Windowing/Input/InputContext.hpp>

namespace Ryn
{
    struct WindowSettings
    {
        u16 Width;
        u16 Height;
        const char* Title;
    };

    class Window
    {
      public:
        InputContext* Input;

      protected:
        Window() { Input = new InputContext(); }

      public:
        virtual ~Window() { delete Input; }

        virtual bool IsRunning() const = 0;

        virtual void Close() = 0;
        virtual void Update() = 0;

        static Window* Create(const WindowSettings& settings);
    };
}
