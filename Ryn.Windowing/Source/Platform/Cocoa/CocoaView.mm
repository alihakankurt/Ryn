#include "CocoaView.hh"

#include <Ryn/Windowing/Events/KeyEvent.hpp>
#include <Ryn/Windowing/Events/MouseEvent.hpp>

@implementation CocoaView

- (instancetype)initWithWindow:(Ryn::CocoaWindow*)window
{
    self = [super init];
    if (self)
    {
        cocoaWindow = window;
    }
    return self;
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)keyDown:(NSEvent*)event
{
    Ryn::Key key = MapCocoaKey([event keyCode]);
    Ryn::ModifierFlags modifiers = MapCocoaModifierFlags([event modifierFlags]);
    Ryn::KeyPressEvent e{key, modifiers};
    cocoaWindow->OnEvent(e);
}

- (void)keyUp:(NSEvent*)event
{
    Ryn::Key key = MapCocoaKey([event keyCode]);
    Ryn::ModifierFlags modifiers = MapCocoaModifierFlags([event modifierFlags]);
    Ryn::KeyReleaseEvent e{key, modifiers};
    cocoaWindow->OnEvent(e);
}

- (void)mouseMoved:(NSEvent*)event
{
    NSPoint location = [event locationInWindow];
    Ryn::f32 x = static_cast<Ryn::f32>(location.x);
    Ryn::f32 y = static_cast<Ryn::f32>(location.y);
    Ryn::MouseMoveEvent e{{x, y}};
    cocoaWindow->OnEvent(e);
}

- (void)scrollWheel:(NSEvent*)event
{
    Ryn::f32 deltaX = static_cast<Ryn::f32>([event scrollingDeltaX]);
    Ryn::f32 deltaY = static_cast<Ryn::f32>([event scrollingDeltaY]);
    Ryn::MouseScrollEvent e{{deltaX, deltaY}};
}

- (void)mouseDown:(NSEvent*)event
{
    Ryn::MouseButton button = Ryn::MouseButton::Left;
    Ryn::ModifierFlags modifiers = MapCocoaModifierFlags([event modifierFlags]);
    Ryn::MouseButtonPressEvent e{button, modifiers};
    cocoaWindow->OnEvent(e);
}

- (void)mouseUp:(NSEvent*)event
{
    Ryn::MouseButton button = Ryn::MouseButton::Left;
    Ryn::ModifierFlags modifiers = MapCocoaModifierFlags([event modifierFlags]);
    Ryn::MouseButtonReleaseEvent e{button, modifiers};
    cocoaWindow->OnEvent(e);
}

- (void)rightMouseDown:(NSEvent*)event
{
    Ryn::MouseButton button = Ryn::MouseButton::Right;
    Ryn::ModifierFlags modifiers = MapCocoaModifierFlags([event modifierFlags]);
    Ryn::MouseButtonPressEvent e{button, modifiers};
    cocoaWindow->OnEvent(e);
}

- (void)rightMouseUp:(NSEvent*)event
{
    Ryn::MouseButton button = Ryn::MouseButton::Right;
    Ryn::ModifierFlags modifiers = MapCocoaModifierFlags([event modifierFlags]);
    Ryn::MouseButtonReleaseEvent e{button, modifiers};
    cocoaWindow->OnEvent(e);
}

- (void)otherMouseDown:(NSEvent*)event
{
    Ryn::MouseButton button = MapCocoaMouseButton([event buttonNumber]);
    Ryn::ModifierFlags modifiers = MapCocoaModifierFlags([event modifierFlags]);
    Ryn::MouseButtonPressEvent e{button, modifiers};
    cocoaWindow->OnEvent(e);
}

- (void)otherMouseUp:(NSEvent*)event
{
    Ryn::MouseButton button = MapCocoaMouseButton([event buttonNumber]);
    Ryn::ModifierFlags modifiers = MapCocoaModifierFlags([event modifierFlags]);
    Ryn::MouseButtonReleaseEvent e{button, modifiers};
    cocoaWindow->OnEvent(e);
}

@end

Ryn::ModifierFlags MapCocoaModifierFlags(NSEventModifierFlags modifiers)
{
    Ryn::ModifierFlags result = Ryn::ModifierFlags::None;
    if (modifiers & NSEventModifierFlagShift)
        result |= Ryn::ModifierFlags::Shift;
    if (modifiers & NSEventModifierFlagControl)
        result |= Ryn::ModifierFlags::Control;
    if (modifiers & NSEventModifierFlagOption)
        result |= Ryn::ModifierFlags::Alt;
    if (modifiers & NSEventModifierFlagCommand)
        result |= Ryn::ModifierFlags::System;
    if (modifiers & NSEventModifierFlagCapsLock)
        result |= Ryn::ModifierFlags::CapsLock;
    return result;
}

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
            NSLog(@"[Cocoa] Unknown button code: %ld", button);
            return Ryn::MouseButton::Unknown;
    }
}
