#pragma once

#include <Ryn/Core.hpp>

namespace Ryn::Windowing
{
    struct WindowSettings
    {
        usz Width;
        usz Height;
        const char* Title;
    };

    class Window
    {
      protected:
        Window() {}

      public:
        virtual ~Window() {}

        virtual bool IsRunning() const = 0;

        virtual void Close() = 0;
        virtual void Update() = 0;

        static Window* Create(const WindowSettings& settings);
    };
}
