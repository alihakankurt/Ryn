#pragma once

namespace Ryn
{
    enum class EventKind
    {
        Unknown,

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

    class Event
    {
      public:
        const EventKind Kind;

      protected:
        Event(EventKind kind) :
            Kind(kind) {}

      public:
        virtual ~Event() {}

        bool Is(EventKind kind) const { return Kind == kind; }

        template <typename TEvent>
        TEvent& As() { return static_cast<TEvent&>(*this); }
    };
}
