#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Mathematics/Vector2.hpp>
#include <Ryn/Windowing/Events/Event.hpp>
#include <Ryn/Windowing/Input/MouseButton.hpp>

namespace Ryn
{
    class MouseMoveEvent : public Event
    {
      public:
        const Vector2<f64> Position;

      public:
        MouseMoveEvent(Vector2<f64> position) :
            Event(EventKind::MouseMove),
            Position(position) {}
    };

    class MouseScrollEvent : public Event
    {
      public:
        const Vector2<f64> Offset;

      public:
        MouseScrollEvent(Vector2<f64> offset) :
            Event(EventKind::MouseScroll),
            Offset(offset) {}
    };

    class MouseButtonPressEvent : public Event
    {
      public:
        const MouseButton Button;

      public:
        MouseButtonPressEvent(MouseButton button) :
            Event(EventKind::MouseButtonPress),
            Button(button) {}
    };

    class MouseButtonReleaseEvent : public Event
    {
      public:
        const MouseButton Button;

      public:
        MouseButtonReleaseEvent(MouseButton button) :
            Event(EventKind::MouseButtonRelease),
            Button(button) {}
    };
}
