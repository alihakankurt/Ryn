#pragma once

#include <Ryn/Core/Utility.hpp>
#include <Ryn/Core/Function.hpp>
#include <Ryn/Mathematics/Vector2.hpp>
#include <Ryn/Windowing/Events/Event.hpp>
#include <Ryn/Windowing/WindowSettings.hpp>

namespace Ryn
{
    class Window
    {
      protected:
        Action<Event> EventCallback;

      public:
        virtual ~Window() {}

        virtual void* GetNativeHandle() const = 0;

        virtual bool IsRunning() const = 0;
        virtual void Close() = 0;

        virtual Vector2<u32> GetSize() const = 0;
        virtual Vector2<u32> GetFramebufferSize() const = 0;
        virtual void Resize(Vector2<u32> size) = 0;

        virtual String GetTitle() const = 0;
        virtual void SetTitle(const String& title) = 0;

      public:
        void SetEventCallback(Action<Event>&& callback) { EventCallback = Utility::Move(callback); }

      public:
        static Window* Create(const WindowSettings& settings);
        static void PollEvents();
    };
}
