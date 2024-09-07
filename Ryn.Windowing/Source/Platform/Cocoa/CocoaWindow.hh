#pragma once

#include <Ryn/Windowing/Window.hpp>

#import <Cocoa/Cocoa.h>

namespace Ryn
{
    class CocoaWindow : public Window
    {
      public:
        CocoaWindow(const WindowSettings& settings);
        virtual ~CocoaWindow() override;

        virtual bool IsRunning() const override;

        virtual void Close() override;

        virtual void Resize(Vector2<u16> size) override;
        virtual void SetTitle(const String& title) override;

        void OnEvent(Event& event) { if (EventCallback) EventCallback(event); }

      private:
        NSWindow* _window;
    };
}
