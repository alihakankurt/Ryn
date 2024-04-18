#ifndef __RYN_WINDOWING_WINDOW_HPP__
#define __RYN_WINDOWING_WINDOW_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    struct WindowConfig
    {
        usize Width;
        usize Height;
        cstring Title;
    };

    class Window
    {
      public:
        virtual ~Window() = default;

        virtual void Update() = 0;
        virtual bool IsActive() const = 0;

        static Window* Create(const WindowConfig& config);
    };
}

#endif