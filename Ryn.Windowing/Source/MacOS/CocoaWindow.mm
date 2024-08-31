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

@implementation CocoaView

- (instancetype)initWithWindow:(Ryn::Windowing::CocoaWindow*)window
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
    _window->Input->SetKeyState(MapCocoaKeyToRynKey([event keyCode]), Ryn::Windowing::Input::KeyState::Pressed);
}

- (void)keyUp:(NSEvent*)event
{
    _window->Input->SetKeyState(MapCocoaKeyToRynKey([event keyCode]), Ryn::Windowing::Input::KeyState::Released);
}

- (void)mouseDown:(NSEvent*)event
{
    _window->Input->SetMouseButtonState(Ryn::Windowing::Input::MouseButton::Left, Ryn::Windowing::Input::MouseButtonState::Pressed);
}

- (void)mouseUp:(NSEvent*)event
{
    _window->Input->SetMouseButtonState(Ryn::Windowing::Input::MouseButton::Left, Ryn::Windowing::Input::MouseButtonState::Released);
}

- (void)rightMouseDown:(NSEvent*)event
{
    _window->Input->SetMouseButtonState(Ryn::Windowing::Input::MouseButton::Right, Ryn::Windowing::Input::MouseButtonState::Pressed);
}

- (void)rightMouseUp:(NSEvent*)event
{
    _window->Input->SetMouseButtonState(Ryn::Windowing::Input::MouseButton::Right, Ryn::Windowing::Input::MouseButtonState::Released);
}

- (void)otherMouseDown:(NSEvent*)event
{
    _window->Input->SetMouseButtonState(MapCocoaMouseButtonToRynMouseButton([event buttonNumber]), Ryn::Windowing::Input::MouseButtonState::Pressed);
}

- (void)otherMouseUp:(NSEvent*)event
{
    _window->Input->SetMouseButtonState(MapCocoaMouseButtonToRynMouseButton([event buttonNumber]), Ryn::Windowing::Input::MouseButtonState::Released);
}

@end

Ryn::Windowing::Input::Key MapCocoaKeyToRynKey(UInt16 keycode)
{
    switch (keycode)
    {
        case 0:     return Ryn::Windowing::Input::Key::A;
        case 1:     return Ryn::Windowing::Input::Key::S;
        case 2:     return Ryn::Windowing::Input::Key::D;
        case 3:     return Ryn::Windowing::Input::Key::F;
        case 4:     return Ryn::Windowing::Input::Key::H;
        case 5:     return Ryn::Windowing::Input::Key::G;
        case 6:     return Ryn::Windowing::Input::Key::Z;
        case 7:     return Ryn::Windowing::Input::Key::X;
        case 8:     return Ryn::Windowing::Input::Key::C;
        case 9:     return Ryn::Windowing::Input::Key::V;
        case 10:    return Ryn::Windowing::Input::Key::Tilde;
        case 11:    return Ryn::Windowing::Input::Key::B;
        case 12:    return Ryn::Windowing::Input::Key::Q;
        case 13:    return Ryn::Windowing::Input::Key::W;
        case 14:    return Ryn::Windowing::Input::Key::E;
        case 15:    return Ryn::Windowing::Input::Key::R;
        case 16:    return Ryn::Windowing::Input::Key::Y;
        case 17:    return Ryn::Windowing::Input::Key::T;
        case 18:    return Ryn::Windowing::Input::Key::One;
        case 19:    return Ryn::Windowing::Input::Key::Two;
        case 20:    return Ryn::Windowing::Input::Key::Three;
        case 21:    return Ryn::Windowing::Input::Key::Four;
        case 22:    return Ryn::Windowing::Input::Key::Six;
        case 23:    return Ryn::Windowing::Input::Key::Five;
        case 24:    return Ryn::Windowing::Input::Key::Equal;
        case 25:    return Ryn::Windowing::Input::Key::Nine;
        case 26:    return Ryn::Windowing::Input::Key::Seven;
        case 27:    return Ryn::Windowing::Input::Key::Minus;
        case 28:    return Ryn::Windowing::Input::Key::Eight;
        case 29:    return Ryn::Windowing::Input::Key::Zero;
        case 30:    return Ryn::Windowing::Input::Key::RightBracket;
        case 31:    return Ryn::Windowing::Input::Key::O;
        case 32:    return Ryn::Windowing::Input::Key::U;
        case 33:    return Ryn::Windowing::Input::Key::LeftBracket;
        case 34:    return Ryn::Windowing::Input::Key::I;
        case 35:    return Ryn::Windowing::Input::Key::P;
        case 36:    return Ryn::Windowing::Input::Key::Enter;
        case 37:    return Ryn::Windowing::Input::Key::L;
        case 38:    return Ryn::Windowing::Input::Key::J;
        case 39:    return Ryn::Windowing::Input::Key::Quote;
        case 40:    return Ryn::Windowing::Input::Key::K;
        case 41:    return Ryn::Windowing::Input::Key::Semicolon;
        case 42:    return Ryn::Windowing::Input::Key::Backslash;
        case 43:    return Ryn::Windowing::Input::Key::Comma;
        case 44:    return Ryn::Windowing::Input::Key::Slash;
        case 45:    return Ryn::Windowing::Input::Key::N;
        case 46:    return Ryn::Windowing::Input::Key::M;
        case 47:    return Ryn::Windowing::Input::Key::Period;
        case 48:    return Ryn::Windowing::Input::Key::Tab;
        case 49:    return Ryn::Windowing::Input::Key::Space;
        case 50:    return Ryn::Windowing::Input::Key::Backtick;
        case 51:    return Ryn::Windowing::Input::Key::Backspace;
        case 53:    return Ryn::Windowing::Input::Key::Escape;
        case 96:    return Ryn::Windowing::Input::Key::F5;
        case 97:    return Ryn::Windowing::Input::Key::F6;
        case 98:    return Ryn::Windowing::Input::Key::F7;
        case 99:    return Ryn::Windowing::Input::Key::F3;
        case 100:   return Ryn::Windowing::Input::Key::F8;
        case 101:   return Ryn::Windowing::Input::Key::F9;
        case 103:   return Ryn::Windowing::Input::Key::F11;
        case 109:   return Ryn::Windowing::Input::Key::F10;
        case 111:   return Ryn::Windowing::Input::Key::F12;
        case 118:   return Ryn::Windowing::Input::Key::F4;
        case 120:   return Ryn::Windowing::Input::Key::F2;
        case 122:   return Ryn::Windowing::Input::Key::F1;
        case 123:   return Ryn::Windowing::Input::Key::Left;
        case 124:   return Ryn::Windowing::Input::Key::Right;
        case 125:   return Ryn::Windowing::Input::Key::Down;
        case 126:   return Ryn::Windowing::Input::Key::Up;
        default:
            NSLog(@"[Cocoa] Unknown key code: %u", keycode);
            return Ryn::Windowing::Input::Key::Unknown;
    }
}

Ryn::Windowing::Input::MouseButton MapCocoaMouseButtonToRynMouseButton(NSInteger button)
{
    switch (button)
    {
        case 0:     return Ryn::Windowing::Input::MouseButton::Button1;
        case 1:     return Ryn::Windowing::Input::MouseButton::Button2;
        case 2:     return Ryn::Windowing::Input::MouseButton::Button3;
        case 3:     return Ryn::Windowing::Input::MouseButton::Button4;
        case 4:     return Ryn::Windowing::Input::MouseButton::Button5;
        case 5:     return Ryn::Windowing::Input::MouseButton::Button6;
        case 6:     return Ryn::Windowing::Input::MouseButton::Button7;
        case 7:     return Ryn::Windowing::Input::MouseButton::Button8;
        default:
            NSLog(@"[Cocoa] Unknown button code: %ld", button);
            return Ryn::Windowing::Input::MouseButton::Unknown;
    }
}

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
