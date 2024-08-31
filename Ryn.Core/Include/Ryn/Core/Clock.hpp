#pragma once

#include <Ryn/Core/Types.hpp>

namespace Ryn::Core
{
    class Clock
    {
      private:
        f64 _start;

      public:
        Clock();

        f64 Restart();

      public:
        static f64 Current();
    };
}
