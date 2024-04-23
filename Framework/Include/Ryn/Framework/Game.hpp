#ifndef __RYN_FRAMEWORK_GAME_HPP__
#define __RYN_FRAMEWORK_GAME_HPP__

#include <Ryn/Core.hpp>
#include <Ryn/Windowing/Window.hpp>
#include <Ryn/Graphics/Renderer.hpp>

namespace Ryn
{
    class Game
    {
      protected:
        Window* Window;
        InputContext* Input;
        Renderer* Renderer;

      public:
        virtual ~Game() = default;

      public:
        void Run();

      protected:
        virtual void Configure(WindowConfig& windowConfig) = 0;
        virtual void Initialize() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Finalize() = 0;

      public:
        static Game* Create();
    };
}

#endif