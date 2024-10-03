#pragma once

#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Function.hpp>
#include <Ryn/Numerics/Vector2.hpp>
#include <Ryn/Windowing/Events/Event.hpp>
#include <Ryn/Windowing/WindowSettings.hpp>

namespace Ryn
{
    class Window
    {
      protected:
        Function<void(Event&)> EventCallback;

      public:
        virtual ~Window() {}

        virtual void* GetNativeHandle() const = 0;

        virtual bool IsRunning() const = 0;

        virtual void Close() = 0;

        virtual void Resize(Vector2<u16> size) = 0;
        virtual void SetTitle(const String& title) = 0;

        virtual Vector2<u16> GetSize() const = 0;
        virtual Vector2<u16> GetFramebufferSize() const = 0;
        virtual String GetTitle() const = 0;

        void SetEventCallback(Function<void(Event&)>&& callback) { EventCallback = Utility::Move(callback); }

        static Window* Create(const WindowSettings& settings);
        static void PollEvents();
    };
}
