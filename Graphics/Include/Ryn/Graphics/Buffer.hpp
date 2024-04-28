#ifndef __RYN_GRAPHICS_BUFFER_HPP__
#define __RYN_GRAPHICS_BUFFER_HPP__

#include <Ryn/Core.hpp>
#include <Ryn/Collections/List.hpp>

namespace Ryn
{
    class BufferLayout
    {
      public:
        enum struct DataKind
        {
            Int32,
            UInt32,
            Float32,
        };

        struct Attribute
        {
            DataKind Kind;
            usize Count;

            usize Size() const;
        };

      private:
        List<Attribute> _attributes;

      public:
        BufferLayout() = default;

        const List<Attribute>& Attributes() const;
        void AddAttribute(Attribute attribute);

        usize Size() const;
    };

    enum struct BufferKind
    {
        Index,
        Vertex,
        Uniform,
    };

    class Buffer
    {
      private:
        BufferLayout _layout;

      public:
        Buffer(BufferLayout layout);
        virtual ~Buffer() = default;

        virtual const BufferLayout& Layout() const;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(const void* data, usize size) = 0;
        virtual void UpdateData(const void* data, usize size, usize offset) = 0;

      public:
        static Ref<Buffer> Create(BufferKind kind, BufferLayout layout);
    };
}

#endif