#ifndef __RYN_WINDOWING_INPUT_INPUT_CONTEXT_HPP__
#define __RYN_WINDOWING_INPUT_INPUT_CONTEXT_HPP__

#include <Ryn/Windowing/Input/Key.hpp>

namespace Ryn
{
    class InputContext
    {
      public:
        virtual ~InputContext() = default;

        virtual bool IsKeyUp(Key key) const = 0;
        virtual bool IsKeyDown(Key key) const = 0;
        virtual bool IsKeyPressed(Key key) const = 0;
        virtual bool IsKeyReleased(Key key) const = 0;
    };
}

#endif