#ifndef __RYN_WINDOWING_WINDOW_HPP__
#define __RYN_WINDOWING_WINDOW_HPP__

#include <Ryn/Core.hpp>
#include <Ryn/Windowing/Input/InputContext.hpp>

namespace Ryn
{
    struct WindowConfig
    {
        usize Width;
        usize Height;
        string Title;
    };

    class Window
    {
      public:
        virtual ~Window() = default;

        virtual void Close() = 0;
        virtual void Update() = 0;
        virtual bool IsActive() const = 0;

        virtual InputContext* GetInputContext() = 0;

        static Window* Create(const WindowConfig& config);
    };
}

#endif