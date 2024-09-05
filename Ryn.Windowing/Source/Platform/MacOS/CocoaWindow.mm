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

- (instancetype)initWithWindow:(Ryn::CocoaWindow*)window
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

@implementation CocoaView

- (instancetype)initWithWindow:(Ryn::CocoaWindow*)window
{
    self = [super init];
    if (self)
    {
        _window = window;
    }
    return self;
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)keyDown:(NSEvent*)event
{
    _window->Input->SetKeyState(MapCocoaKeyToRynKey([event keyCode]), Ryn::KeyState::Pressed);
}

- (void)keyUp:(NSEvent*)event
{
    _window->Input->SetKeyState(MapCocoaKeyToRynKey([event keyCode]), Ryn::KeyState::Released);
}

- (void)mouseDown:(NSEvent*)event
{
    _window->Input->SetButtonState(Ryn::MouseButton::Left, Ryn::MouseButtonState::Pressed);
}

- (void)mouseUp:(NSEvent*)event
{
    _window->Input->SetButtonState(Ryn::MouseButton::Left, Ryn::MouseButtonState::Released);
}

- (void)rightMouseDown:(NSEvent*)event
{
    _window->Input->SetButtonState(Ryn::MouseButton::Right, Ryn::MouseButtonState::Pressed);
}

- (void)rightMouseUp:(NSEvent*)event
{
    _window->Input->SetButtonState(Ryn::MouseButton::Right, Ryn::MouseButtonState::Released);
}

- (void)otherMouseDown:(NSEvent*)event
{
    _window->Input->SetButtonState(MapCocoaMouseButtonToRynMouseButton([event buttonNumber]), Ryn::MouseButtonState::Pressed);
}

- (void)otherMouseUp:(NSEvent*)event
{
    _window->Input->SetButtonState(MapCocoaMouseButtonToRynMouseButton([event buttonNumber]), Ryn::MouseButtonState::Released);
}

@end

Ryn::Key MapCocoaKeyToRynKey(UInt16 keycode)
{
    switch (keycode)
    {
        case 0:     return Ryn::Key::A;
        case 1:     return Ryn::Key::S;
        case 2:     return Ryn::Key::D;
        case 3:     return Ryn::Key::F;
        case 4:     return Ryn::Key::H;
        case 5:     return Ryn::Key::G;
        case 6:     return Ryn::Key::Z;
        case 7:     return Ryn::Key::X;
        case 8:     return Ryn::Key::C;
        case 9:     return Ryn::Key::V;
        case 10:    return Ryn::Key::Tilde;
        case 11:    return Ryn::Key::B;
        case 12:    return Ryn::Key::Q;
        case 13:    return Ryn::Key::W;
        case 14:    return Ryn::Key::E;
        case 15:    return Ryn::Key::R;
        case 16:    return Ryn::Key::Y;
        case 17:    return Ryn::Key::T;
        case 18:    return Ryn::Key::One;
        case 19:    return Ryn::Key::Two;
        case 20:    return Ryn::Key::Three;
        case 21:    return Ryn::Key::Four;
        case 22:    return Ryn::Key::Six;
        case 23:    return Ryn::Key::Five;
        case 24:    return Ryn::Key::Equal;
        case 25:    return Ryn::Key::Nine;
        case 26:    return Ryn::Key::Seven;
        case 27:    return Ryn::Key::Minus;
        case 28:    return Ryn::Key::Eight;
        case 29:    return Ryn::Key::Zero;
        case 30:    return Ryn::Key::RightBracket;
        case 31:    return Ryn::Key::O;
        case 32:    return Ryn::Key::U;
        case 33:    return Ryn::Key::LeftBracket;
        case 34:    return Ryn::Key::I;
        case 35:    return Ryn::Key::P;
        case 36:    return Ryn::Key::Enter;
        case 37:    return Ryn::Key::L;
        case 38:    return Ryn::Key::J;
        case 39:    return Ryn::Key::Quote;
        case 40:    return Ryn::Key::K;
        case 41:    return Ryn::Key::Semicolon;
        case 42:    return Ryn::Key::Backslash;
        case 43:    return Ryn::Key::Comma;
        case 44:    return Ryn::Key::Slash;
        case 45:    return Ryn::Key::N;
        case 46:    return Ryn::Key::M;
        case 47:    return Ryn::Key::Period;
        case 48:    return Ryn::Key::Tab;
        case 49:    return Ryn::Key::Space;
        case 50:    return Ryn::Key::Backtick;
        case 51:    return Ryn::Key::Backspace;
        case 53:    return Ryn::Key::Escape;
        case 96:    return Ryn::Key::F5;
        case 97:    return Ryn::Key::F6;
        case 98:    return Ryn::Key::F7;
        case 99:    return Ryn::Key::F3;
        case 100:   return Ryn::Key::F8;
        case 101:   return Ryn::Key::F9;
        case 103:   return Ryn::Key::F11;
        case 109:   return Ryn::Key::F10;
        case 111:   return Ryn::Key::F12;
        case 118:   return Ryn::Key::F4;
        case 120:   return Ryn::Key::F2;
        case 122:   return Ryn::Key::F1;
        case 123:   return Ryn::Key::Left;
        case 124:   return Ryn::Key::Right;
        case 125:   return Ryn::Key::Down;
        case 126:   return Ryn::Key::Up;
        default:
            NSLog(@"[Cocoa] Unknown key code: %u", keycode);
            return Ryn::Key::Unknown;
    }
}

Ryn::MouseButton MapCocoaMouseButtonToRynMouseButton(NSInteger button)
{
    switch (button)
    {
        case 0:     return Ryn::MouseButton::Button1;
        case 1:     return Ryn::MouseButton::Button2;
        case 2:     return Ryn::MouseButton::Button3;
        case 3:     return Ryn::MouseButton::Button4;
        case 4:     return Ryn::MouseButton::Button5;
        case 5:     return Ryn::MouseButton::Button6;
        case 6:     return Ryn::MouseButton::Button7;
        case 7:     return Ryn::MouseButton::Button8;
        default:
            NSLog(@"[Cocoa] Unknown button code: %ld", button);
            return Ryn::MouseButton::Unknown;
    }
}

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

        NSRect frame = NSMakeRect(0, 0, settings.Width, settings.Height);
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

        Input->Update();
    }

    Window* Window::Create(const WindowSettings& settings)
    {
        return new CocoaWindow(settings);
    }
}
