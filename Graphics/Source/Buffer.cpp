#include <Ryn/Graphics/Buffer.hpp>

#include "OpenGL/OpenGLBuffer.hpp"

namespace Ryn
{
    usize BufferLayout::Attribute::Size() const
    {
        switch (Kind)
        {
            case DataKind::Int32:   return Count * sizeof(i32);
            case DataKind::UInt32:  return Count * sizeof(u32);
            case DataKind::Float32: return Count * sizeof(f32);
        }
    }

    const List<BufferLayout::Attribute>& BufferLayout::Attributes() const
    {
        return _attributes;
    }

    void BufferLayout::AddAttribute(Attribute attribute)
    {
        _attributes.Add(attribute);
    }

    usize BufferLayout::Size() const
    {
        usize stride = 0;
        for (const auto& attribute : _attributes)
            stride += attribute.Size();

        return stride;
    }

    Buffer::Buffer(BufferLayout layout)
    {
        _layout = layout;
    }

    const BufferLayout& Buffer::Layout() const
    {
        return _layout;
    }

    Ref<Buffer> Buffer::Create(BufferKind kind, BufferLayout layout)
    {
        return Ref<Buffer>(new OpenGLBuffer(kind, layout));
    }
}
