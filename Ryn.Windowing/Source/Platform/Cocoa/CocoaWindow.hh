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

        virtual void* GetNativeHandle() const override { return _window; }

        virtual bool IsRunning() const override;
        virtual void Close() override;

        virtual Vector2<u32> GetSize() const override;
        virtual Vector2<u32> GetFramebufferSize() const override;
        virtual void Resize(Vector2<u32> size) override;

        virtual String GetTitle() const override;
        virtual void SetTitle(const String& title) override;

        void OnEvent(const Event& event) { if (EventCallback) EventCallback(event); }

      private:
        NSWindow* _window;
    };
}
