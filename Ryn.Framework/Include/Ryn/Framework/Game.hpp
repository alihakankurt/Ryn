#pragma once

namespace Ryn::Framework
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
