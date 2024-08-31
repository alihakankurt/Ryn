#pragma once

#include <Ryn/Windowing/Window.hpp>

namespace Ryn::Framework
{
    class Game
    {
      protected:
        Windowing::Window* Window;

      public:
        virtual ~Game() = default;

        void Run();

      protected:
        virtual void Configure(Windowing::WindowSettings& settings) = 0;
        virtual void Initialize() = 0;
        virtual void Finalize() = 0;
    };
}
