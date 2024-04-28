#ifndef __RYN_GRAPHICS_OPENGL_BUFFER_HPP__
#define __RYN_GRAPHICS_OPENGL_BUFFER_HPP__

#include <Ryn/Graphics/Buffer.hpp>
#include <Ryn/Native/OpenGL.hpp>

namespace Ryn
{
    static inline constexpr OpenGL::DataType ToOpenGL(BufferLayout::DataKind kind)
    {
        switch (kind)
        {
            case BufferLayout::DataKind::Int32:   return OpenGL::DataType::Int;
            case BufferLayout::DataKind::UInt32:  return OpenGL::DataType::UnsignedInt;
            case BufferLayout::DataKind::Float32: return OpenGL::DataType::Float;
        }
    }

    static inline constexpr OpenGL::BufferTarget ToOpenGL(BufferKind kind)
    {
        switch (kind)
        {
            case BufferKind::Index:   return OpenGL::BufferTarget::ElementArray;
            case BufferKind::Vertex:  return OpenGL::BufferTarget::Array;
            case BufferKind::Uniform: return OpenGL::BufferTarget::Uniform;
        }
    }

    class OpenGLBuffer : public Buffer
    {
      private:
        u32 _rendererId;
        OpenGL::BufferTarget _target;

      public:
        OpenGLBuffer(BufferKind kind, BufferLayout layout);
        virtual ~OpenGLBuffer() override;

        u32 GetRendererId() const;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetData(const void* data, usize size) override;
        virtual void UpdateData(const void* data, usize size, usize offset) override;
    };
}

#endif