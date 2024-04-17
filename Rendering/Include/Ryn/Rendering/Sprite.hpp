#ifndef __RYN_RENDERING_SPRITE_HPP__
#define __RYN_RENDERING_SPRITE_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    class Sprite
    {
      public:
        virtual ~Sprite() = default;

        virtual void Update(f32 deltaTime) = 0;
        virtual void Render() = 0;
    };
}

#endif