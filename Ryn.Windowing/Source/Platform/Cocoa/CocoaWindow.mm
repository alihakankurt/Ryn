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
        _window = [[NSWindow alloc]
            initWithContentRect:frame
            styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable)
            backing:NSBackingStoreBuffered
            defer:NO];

        CocoaWindowDelegate* windowDelegate = [[CocoaWindowDelegate alloc] initWithWindow:this];
        [_window setDelegate:windowDelegate];
        [windowDelegate release];

        CocoaView* view = [[CocoaView alloc] initWithWindow:this];
        [_window setContentView:view];
        [view release];

        [_window setTitle:[NSString stringWithUTF8String:settings.Title.Data()]];
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

    Vector2<u32> CocoaWindow::GetSize() const
    {
        NSView* contentView = [_window contentView];
        const NSRect contentRect = [contentView frame];
        u32 width = static_cast<u32>(contentRect.size.width);
        u32 height = static_cast<u32>(contentRect.size.height);
        return Vector2<u32>{width, height};
    }

    Vector2<u32> CocoaWindow::GetFramebufferSize() const
    {
        NSView* contentView = [_window contentView];
        const NSRect contentRect = [contentView frame];
        const NSRect backingRect = [contentView convertRectToBacking:contentRect];
        u32 width = static_cast<u32>(backingRect.size.width);
        u32 height = static_cast<u32>(backingRect.size.height);
        return Vector2<u32>{width, height};
    }

    void CocoaWindow::Resize(Vector2<u32> size)
    {
        if ([_window isResizable] == NO)
            return;

        NSRect contentRect = [_window contentRectForFrameRect:[_window frame]];
        contentRect.size = NSMakeSize(static_cast<CGFloat>(size.X), static_cast<CGFloat>(size.Y));
        [_window setFrame:[_window frameRectForContentRect:contentRect] display:YES animate:YES];
    }

    String CocoaWindow::GetTitle() const
    {
        const char* title = [[_window title] UTF8String];
        usz length = String::Length(title);
        char* buffer = Memory::Allocate<char>(length + 1);
        Memory::Copy(buffer, title, length);
        buffer[length] = '\0';
        return String{length, buffer};
    }

    void CocoaWindow::SetTitle(const String& title)
    {
        [_window setTitle:[NSString stringWithUTF8String:title.Data()]];
    }

    Window* Window::Create(const WindowSettings& settings)
    {
        return Memory::Allocate<CocoaWindow>(settings);
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
