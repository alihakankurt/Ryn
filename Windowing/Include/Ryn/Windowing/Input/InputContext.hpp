#ifndef __RYN_WINDOWING_INPUT_INPUT_CONTEXT_HPP__
#define __RYN_WINDOWING_INPUT_INPUT_CONTEXT_HPP__

#include <Ryn/Windowing/Input/Keys.hpp>

namespace Ryn
{
    class InputContext
    {
      public:
        virtual ~InputContext() = default;

        virtual bool IsKeyUp(Keys key) const = 0;
        virtual bool IsKeyDown(Keys key) const = 0;
        virtual bool IsKeyPressed(Keys key) const = 0;
        virtual bool IsKeyReleased(Keys key) const = 0;
    };
}

#endif