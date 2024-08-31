#pragma once

#include <Ryn/Core.hpp>
#include <Ryn/Windowing/Input/Key.hpp>

namespace Ryn::Windowing::Input
{
    class InputContext
    {
      private:
        KeyState _keys[static_cast<Core::usz>(Key::Count)] = {KeyState::Up};

      public:
        bool IsKeyUp(Key key) const;
        bool IsKeyDown(Key key) const;
        bool IsKeyPressed(Key key) const;
        bool IsKeyReleased(Key key) const;

        KeyState GetKeyState(Key key) const;
        void SetKeyState(Key key, KeyState state);

        void Update();
    };
}
