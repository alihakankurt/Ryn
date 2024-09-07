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
    Ryn::f32 x = static_cast<Ryn::f32>(frame.origin.x);
    Ryn::f32 y = static_cast<Ryn::f32>(frame.origin.y);
    Ryn::WindowMoveEvent e{{x, y}};
    cocoaWindow->OnEvent(e);
}

- (void)windowDidResize:(NSNotification*)notification
{
    NSWindow* window = [notification object];
    NSRect frame = [window frame];
    Ryn::u32 width = static_cast<Ryn::u32>(frame.size.width);
    Ryn::u32 height = static_cast<Ryn::u32>(frame.size.height);
    Ryn::WindowResizeEvent e{{width, height}};
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
