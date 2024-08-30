#pragma once

namespace Ryn
{
    class Game
    {
      public:
        virtual ~Game() = default;

        void Run();

        virtual void Initialize() = 0;
        virtual void Finalize() = 0;
    };
}
