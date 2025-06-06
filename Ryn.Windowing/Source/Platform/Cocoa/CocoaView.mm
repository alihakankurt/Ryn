#include "CocoaView.hh"

#include <Ryn/IO/Log.hpp>
#include <Ryn/Windowing/Events/KeyEvent.hpp>
#include <Ryn/Windowing/Events/MouseEvent.hpp>

@implementation CocoaView

- (instancetype)initWithWindow:(Ryn::CocoaWindow*)window
{
    self = [super init];
    if (self)
    {
        cocoaWindow = window;
        trackingArea = nil;
        metalLayer = [CAMetalLayer layer];
        [self setLayer:metalLayer];
        [self setWantsLayer:YES];
    }
    return self;
}

- (void)dealloc
{
    [metalLayer release];
    [trackingArea release];
    [super dealloc];
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (BOOL)canBecomeKeyView
{
    return YES;
}

- (BOOL)wantsUpdateLayer
{
    return YES;
}

- (void)updateTrackingAreas
{
    if (trackingArea)
    {
        [self removeTrackingArea:trackingArea];
        [trackingArea release];
    }

    NSTrackingAreaOptions options = NSTrackingMouseEnteredAndExited |
                                    NSTrackingMouseMoved |
                                    NSTrackingActiveInKeyWindow |
                                    NSTrackingInVisibleRect;

    trackingArea = [[NSTrackingArea alloc] initWithRect:[self bounds]
                                           options:options
                                           owner:self
                                           userInfo:nil];

    [self addTrackingArea:trackingArea];
    [super updateTrackingAreas];
}

- (void)viewDidChangeBackingProperties
{
    [metalLayer setContentsScale:[static_cast<NSWindow*>(cocoaWindow->GetNativeHandle()) backingScaleFactor]];
}

- (void)keyDown:(NSEvent*)event
{
    Ryn::Key key = MapCocoaKey([event keyCode]);
    const char* chars = [[event characters] UTF8String];
    Ryn::Span<const char> text{Ryn::String::Length(chars), chars};

    Ryn::KeyPressEvent e{key, text};
    cocoaWindow->OnEvent(e);
}

- (void)keyUp:(NSEvent*)event
{
    Ryn::Key key = MapCocoaKey([event keyCode]);
    const char* chars = [[event characters] UTF8String];
    Ryn::Span<const char> text{Ryn::String::Length(chars), chars};

    Ryn::KeyReleaseEvent e{key, text};
    cocoaWindow->OnEvent(e);
}

- (void)flagsChanged:(NSEvent*)event
{
    Ryn::Key key = MapCocoaKey([event keyCode]);

    NSEventModifierFlags flag = 0;
    switch (key)
    {
        case Ryn::Key::LeftShift:
        case Ryn::Key::RightShift:
            flag = NSEventModifierFlagShift;
            break;

        case Ryn::Key::LeftControl:
        case Ryn::Key::RightControl:
            flag = NSEventModifierFlagControl;
            break;

        case Ryn::Key::LeftAlt:
        case Ryn::Key::RightAlt:
            flag = NSEventModifierFlagOption;
            break;

        case Ryn::Key::LeftSystem:
        case Ryn::Key::RightSystem:
            flag = NSEventModifierFlagCommand;
            break;

        case Ryn::Key::CapsLock:
            flag = NSEventModifierFlagCapsLock;
            break;

        case Ryn::Key::Function:
            flag = NSEventModifierFlagFunction;
            break;

        default:
            Ryn::Log::Warn("Unhandled Cocoa key flag: ", +key);
            return;
    }

    if ([event modifierFlags] & flag)
    {
        Ryn::KeyPressEvent e{key, {}};
        cocoaWindow->OnEvent(e);
    }
    else
    {
        Ryn::KeyReleaseEvent e{key, {}};
        cocoaWindow->OnEvent(e);
    }
}

- (void)mouseMoved:(NSEvent*)event
{
    NSPoint location = [event locationInWindow];
    Ryn::Vector2<Ryn::f64> position{
        static_cast<Ryn::f64>(location.x),
        static_cast<Ryn::f64>(location.y)
    };

    Ryn::MouseMoveEvent e{position};
    cocoaWindow->OnEvent(e);
}

- (void)scrollWheel:(NSEvent*)event
{
    if (![event hasPreciseScrollingDeltas])
    {
        Ryn::Vector2<Ryn::f64> offset{
            static_cast<Ryn::f64>([event scrollingDeltaX]),
            static_cast<Ryn::f64>([event scrollingDeltaY])
        };

        Ryn::MouseScrollEvent e{offset};
        cocoaWindow->OnEvent(e);
    }
}

- (void)mouseDown:(NSEvent*)event
{
    Ryn::MouseButton button = Ryn::MouseButton::Left;
    Ryn::MouseButtonPressEvent e{button};
    cocoaWindow->OnEvent(e);
}

- (void)mouseUp:(NSEvent*)event
{
    Ryn::MouseButton button = Ryn::MouseButton::Left;
    Ryn::MouseButtonReleaseEvent e{button};
    cocoaWindow->OnEvent(e);
}

- (void)rightMouseDown:(NSEvent*)event
{
    Ryn::MouseButton button = Ryn::MouseButton::Right;
    Ryn::MouseButtonPressEvent e{button};
    cocoaWindow->OnEvent(e);
}

- (void)rightMouseUp:(NSEvent*)event
{
    Ryn::MouseButton button = Ryn::MouseButton::Right;
    Ryn::MouseButtonReleaseEvent e{button};
    cocoaWindow->OnEvent(e);
}

- (void)otherMouseDown:(NSEvent*)event
{
    Ryn::MouseButton button = MapCocoaMouseButton([event buttonNumber]);
    Ryn::MouseButtonPressEvent e{button};
    cocoaWindow->OnEvent(e);
}

- (void)otherMouseUp:(NSEvent*)event
{
    Ryn::MouseButton button = MapCocoaMouseButton([event buttonNumber]);
    Ryn::MouseButtonReleaseEvent e{button};
    cocoaWindow->OnEvent(e);
}

@end

Ryn::Key MapCocoaKey(UInt16 keycode)
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
        case 18:    return Ryn::Key::Num1;
        case 19:    return Ryn::Key::Num2;
        case 20:    return Ryn::Key::Num3;
        case 21:    return Ryn::Key::Num4;
        case 22:    return Ryn::Key::Num6;
        case 23:    return Ryn::Key::Num5;
        case 24:    return Ryn::Key::Equal;
        case 25:    return Ryn::Key::Num9;
        case 26:    return Ryn::Key::Num7;
        case 27:    return Ryn::Key::Minus;
        case 28:    return Ryn::Key::Num8;
        case 29:    return Ryn::Key::Num0;
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
        case 54:    return Ryn::Key::RightSystem;
        case 55:    return Ryn::Key::LeftSystem;
        case 56:    return Ryn::Key::LeftShift;
        case 57:    return Ryn::Key::CapsLock;
        case 58:    return Ryn::Key::LeftAlt;
        case 59:    return Ryn::Key::LeftControl;
        case 60:    return Ryn::Key::RightShift;
        case 61:    return Ryn::Key::RightAlt;
        case 62:    return Ryn::Key::RightControl;
        case 63:    return Ryn::Key::Function;
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
            Ryn::Log::Warn("Unmapped Cocoa key code: ", static_cast<Ryn::u16>(keycode));
            return Ryn::Key::Unknown;
    }
}

Ryn::MouseButton MapCocoaMouseButton(NSInteger button)
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
            Ryn::Log::Warn("Unmapped Cocoa mouse button: ", static_cast<Ryn::isz>(button));
            return Ryn::MouseButton::Unknown;
    }
}
