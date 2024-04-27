#ifndef __RYN_GRAPHICS_RENDERER_HPP__
#define __RYN_GRAPHICS_RENDERER_HPP__

#include <Ryn/Core.hpp>
#include <Ryn/Mathematics.hpp>
#include <Ryn/Graphics/Color.hpp>

namespace Ryn
{
    class Renderer
    {
      public:
        virtual ~Renderer() = default;

        virtual void Present() = 0;

        virtual void Clear() = 0;
        virtual void SetClearColor(const Color& color) = 0;

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;

        virtual void DrawQuad(const Vector2<f32>& position, const Vector2<f32>& size, const Color& color) = 0;

      public:
        static Ref<Renderer> Create();
    };
}

#endif