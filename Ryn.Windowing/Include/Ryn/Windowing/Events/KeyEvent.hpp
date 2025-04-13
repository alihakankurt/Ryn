#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Core/Span.hpp>
#include <Ryn/Mathematics/Vector2.hpp>
#include <Ryn/Windowing/Events/Event.hpp>
#include <Ryn/Windowing/Input/Key.hpp>

namespace Ryn
{
    class KeyPressEvent : public Event
    {
      public:
        const Key Key;
        Span<const char> Text;

      public:
        KeyPressEvent(Ryn::Key key, Span<const char> text) :
            Event(EventKind::KeyPress),
            Key(key),
            Text(text) {}
    };

    class KeyReleaseEvent : public Event
    {
      public:
        const Key Key;
        Span<const char> Text;

      public:
        KeyReleaseEvent(Ryn::Key key, Span<const char> text) :
            Event(EventKind::KeyRelease),
            Key(key),
            Text(text) {}
    };
}
