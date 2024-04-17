#ifndef RYN_FRAMEWORK_GAME
#define RYN_FRAMEWORK_GAME

#include <Ryn/Core.hpp>
#include <Ryn/Windowing/Window.hpp>
#include <Ryn/Rendering/Renderer.hpp>

namespace Ryn
{
    class Game
    {
      protected:
        Window* Window;
        Renderer* Renderer;

      public:
        virtual ~Game() = default;

      public:
        void Run();

      protected:
        virtual void Initialize(WindowConfig& windowConfig) = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Finalize() = 0;
    };
}

#endif