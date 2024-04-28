#include "OpenGL/OpenGLBuffer.hpp"

namespace Ryn
{
    OpenGLBuffer::OpenGLBuffer(BufferKind kind, BufferLayout layout) :
        Buffer(layout)
    {
        _target = ToOpenGL(kind);
        OpenGL::CreateBuffer(1, &_rendererId);
    }

    OpenGLBuffer::~OpenGLBuffer()
    {
        OpenGL::DeleteBuffer(1, &_rendererId);
    }

    u32 OpenGLBuffer::GetRendererId() const
    {
        return _rendererId;
    }

    void OpenGLBuffer::Bind() const
    {
        OpenGL::BindBuffer(_target, _rendererId);
    }

    void OpenGLBuffer::Unbind() const
    {
        OpenGL::BindBuffer(_target, 0);
    }

    void OpenGLBuffer::SetData(const void* data, usize size)
    {
        Bind();
        OpenGL::BufferData(_target, size, data, OpenGL::BufferUsage::DynamicDraw);
    }

    void OpenGLBuffer::UpdateData(const void* data, usize size, usize offset)
    {
        Bind();
        OpenGL::BufferSubData(_target, offset, size, data);
    }
}
