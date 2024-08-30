#include "CocoaWindow.hh"

@implementation CocoaApplicationDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notification
{
    NSEvent* event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
        location:NSMakePoint(0, 0)
        modifierFlags:0
        timestamp:0
        windowNumber:0
        context:nil
        subtype:0
        data1:0
        data2:0];

    [NSApp postEvent:event atStart:YES];
    [NSApp stop:nil];
}

@end

@implementation CocoaWindowDelegate

- (instancetype)initWithWindow:(Ryn::Windowing::CocoaWindow*)window
{
    self = [super init];
    if (self)
    {
        _window = window;
    }
    return self;
}

- (BOOL)windowShouldClose:(NSWindow*)sender
{
    _window->Close();
    return YES;
}

- (void)windowDidResize:(NSNotification*)notification
{
    NSLog(@"Window did resize");
}

@end

namespace Ryn::Windowing
{
    CocoaWindow::CocoaWindow(const WindowSettings& settings)
    {
        if (NSApp == nil)
        {
            [NSApplication sharedApplication];
            [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
            [NSApp activateIgnoringOtherApps:YES];

            CocoaApplicationDelegate* appDelegate = [[CocoaApplicationDelegate alloc] init];
            [NSApp setDelegate:appDelegate];
            [appDelegate release];
        }

        NSRect frame = NSMakeRect(0, 0, settings.Width, settings.Height);
        _window = [[NSWindow alloc] initWithContentRect:frame
            styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable)
            backing:NSBackingStoreBuffered
            defer:NO];

        CocoaWindowDelegate* windowDelegate = [[CocoaWindowDelegate alloc] initWithWindow:this];
        [_window setDelegate:windowDelegate];
        [windowDelegate release];

        [_window setTitle:[NSString stringWithUTF8String:settings.Title]];
        [_window makeKeyAndOrderFront:nil];
        [_window center];

        if (![[NSRunningApplication currentApplication] isFinishedLaunching])
        {
            [NSApp run];
        }
    }

    CocoaWindow::~CocoaWindow()
    {
        Close();
    }

    bool CocoaWindow::IsRunning() const
    {
        return _window != nil;
    }

    void CocoaWindow::Close()
    {
        if (_window != nil)
        {
            [_window setDelegate:nil];
            [_window close];
            [_window release];
            _window = nil;

            if ([[NSApp windows] count] == 0)
            {
                [NSApp setDelegate:nil];
                [NSApp release];
            }
        }
    }

    void CocoaWindow::Update()
    {
        NSEvent* event;
        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
            untilDate:[NSDate distantPast]
            inMode:NSDefaultRunLoopMode
            dequeue:YES]))
        {
            [NSApp sendEvent:event];
        }
    }

    Window* Window::Create(const WindowSettings& settings)
    {
        return new CocoaWindow(settings);
    }
}
