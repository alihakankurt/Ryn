#pragma once

#include <Ryn/Windowing/Window.hpp>
#include <Ryn/Windowing/Input/Key.hpp>
#include <Ryn/Windowing/Input/MouseButton.hpp>

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

@interface CocoaView : NSView
{
    Ryn::Windowing::CocoaWindow* _window;
}

- (instancetype)initWithWindow:(Ryn::Windowing::CocoaWindow*)window;

@end

static Ryn::Windowing::Input::Key MapCocoaKeyToRynKey(UInt16 keycode);
static Ryn::Windowing::Input::MouseButton MapCocoaMouseButtonToRynMouseButton(NSInteger button);
