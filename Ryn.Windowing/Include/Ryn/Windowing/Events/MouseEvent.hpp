#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Numerics/Vector2.hpp>
#include <Ryn/Windowing/Events/Event.hpp>
#include <Ryn/Windowing/Input/MouseButton.hpp>
#include <Ryn/Windowing/Input/ModifierFlags.hpp>

namespace Ryn
{
    class MouseMoveEvent : public Event
    {
      public:
        const Vector2<f32> Position;

      public:
        MouseMoveEvent(Vector2<f32> position) :
            Event(EventKind::MouseMove),
            Position(position) {}
    };

    class MouseScrollEvent : public Event
    {
      public:
        const Vector2<f32> Offset;

      public:
        MouseScrollEvent(Vector2<f32> offset) :
            Event(EventKind::MouseScroll),
            Offset(offset) {}
    };

    class MouseButtonPressEvent : public Event
    {
      public:
        const MouseButton Button;
        const ModifierFlags Modifiers;

      public:
        MouseButtonPressEvent(MouseButton button, ModifierFlags modifiers) :
            Event(EventKind::MouseButtonPress),
            Button(button),
            Modifiers(modifiers) {}
    };

    class MouseButtonReleaseEvent : public Event
    {
      public:
        const MouseButton Button;
        const ModifierFlags Modifiers;

      public:
        MouseButtonReleaseEvent(MouseButton button, ModifierFlags modifiers) :
            Event(EventKind::MouseButtonRelease),
            Button(button),
            Modifiers(modifiers) {}
    };
}
