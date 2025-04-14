#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn
{
    enum class EventKind
    {
        WindowClose,
        WindowMove,
        WindowResize,
        WindowFocus,
        WindowLostFocus,

        KeyPress,
        KeyRelease,

        MouseMove,
        MouseScroll,
        MouseButtonPress,
        MouseButtonRelease,
    };

    constexpr usz operator+(EventKind kind) { return static_cast<usz>(kind); }

    class Event
    {
      public:
        EventKind Kind;

      protected:
        Event(EventKind kind) :
            Kind(kind) {}

      public:
        virtual ~Event() {}

        bool Is(EventKind kind) const { return Kind == kind; }

        template <typename TEvent>
        const TEvent& As() const
        {
            return static_cast<const TEvent&>(*this);
        }
    };
}
