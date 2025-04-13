#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Mathematics/Vector2.hpp>
#include <Ryn/Windowing/Events/Event.hpp>

namespace Ryn
{
    class WindowCloseEvent : public Event
    {
      public:
        WindowCloseEvent() :
            Event(EventKind::WindowClose) {}
    };

    class WindowMoveEvent : public Event
    {
      public:
        const Vector2<f64> Position;

      public:
        WindowMoveEvent(Vector2<f64> position) :
            Event(EventKind::WindowMove),
            Position(position) {}
    };

    class WindowResizeEvent : public Event
    {
      public:
        const Vector2<u32> Size;

      public:
        WindowResizeEvent(Vector2<u32> size) :
            Event(EventKind::WindowResize),
            Size(size) {}
    };

    class WindowFocusEvent : public Event
    {
      public:
        WindowFocusEvent() :
            Event(EventKind::WindowFocus) {}
    };

    class WindowLostFocusEvent : public Event
    {
      public:
        WindowLostFocusEvent() :
            Event(EventKind::WindowLostFocus) {}
    };
}
