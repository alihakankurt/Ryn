#include "CocoaWindow.hh"
#include "CocoaApplicationDelegate.hh"
#include "CocoaWindowDelegate.hh"
#include "CocoaView.hh"

namespace Ryn
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

        NSRect frame = NSMakeRect(0, 0, settings.Size.X, settings.Size.Y);
        _window = [[NSWindow alloc] initWithContentRect:frame
            styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable)
            backing:NSBackingStoreBuffered
            defer:NO];

        CocoaWindowDelegate* windowDelegate = [[CocoaWindowDelegate alloc] initWithWindow:this];
        [_window setDelegate:windowDelegate];
        [windowDelegate release];

        CocoaView* view = [[CocoaView alloc] initWithWindow:this];
        [_window setContentView:view];
        [view release];

        [_window setTitle:[NSString stringWithUTF8String:&settings.Title[0]]];
        [_window makeKeyAndOrderFront:nil];
        [_window setAcceptsMouseMovedEvents:YES];
        [_window center];

        if ([[NSRunningApplication currentApplication] isFinishedLaunching])
        {
            [NSApp run];
        }
    }

    CocoaWindow::~CocoaWindow()
    {
        if (IsRunning())
        {
            Close();
        }
    }

    bool CocoaWindow::IsRunning() const
    {
        return _window != nil;
    }

    void CocoaWindow::Close()
    {
        [_window setDelegate:nil];
        [_window close];
        [_window release];
        _window = nil;
    }

    void CocoaWindow::Resize(Vector2<u16> size)
    {
        if ([_window isResizable] == NO)
            return;

        NSRect frame = [_window frame];
        frame.size.width = size.X;
        frame.size.height = size.Y;
        [_window setFrame:frame display:YES animate:YES];
    }

    void CocoaWindow::SetTitle(const String& title)
    {
        [_window setTitle:[NSString stringWithUTF8String:&title[0]]];
    }

    Vector2<u16> CocoaWindow::GetSize() const
    {
        const NSRect contentRect = [_window frame];
        u16 width = static_cast<u16>(contentRect.size.width);
        u16 height = static_cast<u16>(contentRect.size.height);
        return Vector2<u16>(width, height);
    }

    Vector2<u16> CocoaWindow::GetFramebufferSize() const
    {
        const NSRect contentRect = [_window frame];
        const NSRect backingRect = [_window convertRectToBacking:contentRect];
        u16 width = static_cast<u16>(backingRect.size.width);
        u16 height = static_cast<u16>(backingRect.size.height);
        return Vector2<u16>(width, height);
    }

    String CocoaWindow::GetTitle() const
    {
        const NSString* title = [_window title];
        u32 length = static_cast<u32>([title lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
        char* buffer = new char[length];
        memcpy(buffer, [title UTF8String], length);
        return String(buffer, length);
    }

    Window* Window::Create(const WindowSettings& settings)
    {
        return new CocoaWindow(settings);
    }

    void Window::PollEvents()
    {
        NSEvent* event;
        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny untilDate:nil inMode:NSDefaultRunLoopMode dequeue:YES]) != nil)
        {
            [NSApp sendEvent:event];
        }
    }
}
