#pragma once

#include <Ryn/Windowing/Window.hpp>

namespace Ryn
{
    class Game
    {
      protected:
        Window* Window;

      public:
        virtual ~Game() {}

        void Run();

      protected:
        virtual void Configure(WindowSettings& settings) = 0;
        virtual void Initialize() = 0;
        virtual void Finalize() = 0;
    };
}
