#ifndef __RYN_RENDERING_RENDERER_HPP__
#define __RYN_RENDERING_RENDERER_HPP__

#include <Ryn/Core.hpp>
#include <Ryn/Rendering/Color.hpp>

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