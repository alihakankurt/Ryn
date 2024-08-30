#pragma once

#include <Ryn/Windowing/Window.hpp>

#import <Cocoa/Cocoa.h>

namespace Ryn::Windowing
{
    class CocoaWindow : public Window
    {
      public:
        CocoaWindow(const WindowSettings& settings);
        virtual ~CocoaWindow() override;

        virtual bool IsRunning() const override;

        virtual void Close() override;
        virtual void Update() override;

      private:
        NSWindow* _window;
    };
}

@interface CocoaApplicationDelegate : NSObject <NSApplicationDelegate>
@end

@interface CocoaWindowDelegate : NSObject <NSWindowDelegate>
{
    Ryn::Windowing::CocoaWindow* _window;
}

- (instancetype)initWithWindow:(Ryn::Windowing::CocoaWindow*)window;

@end
