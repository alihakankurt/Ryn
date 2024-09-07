#pragma once

#include <Ryn/Windowing/Events/Event.hpp>
#include <Ryn/Windowing/Window.hpp>
#include <Ryn/Framework/InputContext.hpp>

namespace Ryn
{
    class Game
    {
      protected:
        Window* Window;
        InputContext* Input;

      public:
        virtual ~Game() {}

        void Run();

      protected:
        virtual void Configure(WindowSettings& settings) = 0;
        virtual void Initialize() = 0;
        virtual void Finalize() = 0;

      private:
        void OnEvent(Event& event);
    };
}
