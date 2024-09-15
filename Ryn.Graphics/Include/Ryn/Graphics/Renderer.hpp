#pragma once

#include <Ryn/Windowing/Window.hpp>

namespace Ryn
{
    class Renderer
    {
      public:
        virtual ~Renderer() {}

      public:
        static Renderer* Create(const Window& window);
    };
}
