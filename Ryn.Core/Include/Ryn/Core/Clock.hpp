#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Core
{
    class Clock
    {
      private:
        f32 _start;

      public:
        Clock();

        f32 Restart();

      public:
        static f32 Current();
    };
}
