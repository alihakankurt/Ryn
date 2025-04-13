#include "CocoaWindowDelegate.hh"

#include <Ryn/Windowing/Events/WindowEvent.hpp>

@implementation CocoaWindowDelegate

- (id)initWithWindow:(Ryn::CocoaWindow*)window
{
    self = [super init];
    if (self)
    {
        cocoaWindow = window;
    }
    return self;
}

- (BOOL)windowShouldClose:(NSNotification*)notification
{
    cocoaWindow->Close();
    return YES;
}

- (void)windowDidMove:(NSNotification*)notification
{
    NSWindow* window = [notification object];
    NSRect frame = [window frame];
    Ryn::Vector2<Ryn::f64> position{
        static_cast<Ryn::f64>(frame.origin.x),
        static_cast<Ryn::f64>(frame.origin.y)
    };

    Ryn::WindowMoveEvent e{position};
    cocoaWindow->OnEvent(e);
}

- (void)windowDidResize:(NSNotification*)notification
{
    NSWindow* window = [notification object];
    NSRect frame = [window frame];
    Ryn::Vector2<Ryn::u32> size{
        static_cast<Ryn::u32>(frame.size.width),
        static_cast<Ryn::u32>(frame.size.height)
    };

    Ryn::WindowResizeEvent e{size};
    cocoaWindow->OnEvent(e);
}

- (void)windowDidBecomeKey:(NSNotification*)notification
{
    Ryn::WindowFocusEvent e;
    cocoaWindow->OnEvent(e);
}

- (void)windowDidResignKey:(NSNotification*)notification
{
    Ryn::WindowLostFocusEvent e;
    cocoaWindow->OnEvent(e);
}

@end
