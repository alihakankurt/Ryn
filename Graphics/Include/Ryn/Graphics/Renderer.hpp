#ifndef __RYN_GRAPHICS_RENDERER_HPP__
#define __RYN_GRAPHICS_RENDERER_HPP__

#include <Ryn/Core.hpp>
#include <Ryn/Graphics/Color.hpp>

namespace Ryn
{
    class Renderer
    {
      public:
        virtual ~Renderer() = default;

        virtual void Clear() = 0;
        virtual void SetClearColor(const Color& color) = 0;

        static Renderer* Create();
    };
}

#endif