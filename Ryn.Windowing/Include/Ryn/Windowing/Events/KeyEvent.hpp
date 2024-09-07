#pragma once

#include <Ryn/Core/Types.hpp>
#include <Ryn/Numerics/Vector2.hpp>
#include <Ryn/Windowing/Events/Event.hpp>
#include <Ryn/Windowing/Input/Key.hpp>
#include <Ryn/Windowing/Input/ModifierFlags.hpp>

namespace Ryn
{
    class KeyPressEvent : public Event
    {
      public:
        const Key Key;
        const ModifierFlags Modifiers;

      public:
        KeyPressEvent(Ryn::Key key, ModifierFlags modifiers) :
            Event(EventKind::KeyPress),
            Key(key),
            Modifiers(modifiers) {}
    };

    class KeyReleaseEvent : public Event
    {
      public:
        const Key Key;
        const ModifierFlags Modifiers;

      public:
        KeyReleaseEvent(Ryn::Key key, ModifierFlags modifiers) :
            Event(EventKind::KeyRelease),
            Key(key),
            Modifiers(modifiers) {}
    };
}
