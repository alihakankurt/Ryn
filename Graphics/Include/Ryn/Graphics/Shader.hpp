#ifndef __RYN_GRAPHICS_SHADER_HPP__
#define __RYN_GRAPHICS_SHADER_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    class Shader
    {
      public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Ref<Shader> Create(const string& vertexSource, const string& fragmentSource);
    };
}

#endif