#include <Ryn/Native/OpenGL.hpp>
#include <Ryn/IO/File.hpp>

#include "OpenGL/OpenGLRenderer.hpp"
#include "OpenGL/OpenGLBuffer.hpp"

namespace Ryn
{
    OpenGLRenderer::OpenGLRenderer()
    {
        // Create VertexArrayObject
        OpenGL::CreateVertexArray(1, &_vao);
        OpenGL::BindVertexArray(_vao);

        // Setup index buffer data
        u32 indices[IndexCount];
        for (u32 i = 0, j = 0; i < IndexCount; i += IndexPerQuad, j += VertexPerQuad)
        {
            indices[i + 0] = j + 0;
            indices[i + 1] = j + 1;
            indices[i + 2] = j + 2;
            indices[i + 3] = j + 1;
            indices[i + 4] = j + 2;
            indices[i + 5] = j + 3;
        }

        // Create index buffer
        BufferLayout indexBufferLayout;
        indexBufferLayout.AddAttribute({BufferLayout::DataKind::UInt32, 1});

        _indexBuffer = Buffer::Create(BufferKind::Index, indexBufferLayout);
        _indexBuffer->SetData(indices, sizeof(indices));

        // Create vertex buffer
        BufferLayout vertexBufferLayout;
        vertexBufferLayout.AddAttribute({BufferLayout::DataKind::Float32, 2});
        vertexBufferLayout.AddAttribute({BufferLayout::DataKind::Float32, 4});

        _vertexBuffer = Buffer::Create(BufferKind::Vertex, vertexBufferLayout);
        _vertexBuffer->SetData(nullptr, VertexSize * VertexCount);

        // Setup vertex buffer layout
        u32 attributeIndex = 0;
        usize vertexSize = vertexBufferLayout.Size();
        usize vertexOffset = 0;
        for (const auto& attribute : vertexBufferLayout.Attributes())
        {
            usize currentSize = attribute.Size();
            OpenGL::EnableVertexAttribArray(attributeIndex);
            OpenGL::VertexAttribPointer(attributeIndex, As<i32>(attribute.Count), ToOpenGL(attribute.Kind), false, As<isize>(vertexSize), As<void*>(vertexOffset));
            vertexOffset += currentSize;
            attributeIndex++;
        }

        // Create color shader
        string vertexShaderSource = File::Read("./Shaders/Color.vert");
        string fragmentShaderSource = File::Read("./Shaders/Color.frag");
        _colorShader = Shader::Create(vertexShaderSource, fragmentShaderSource);
    }

    OpenGLRenderer::~OpenGLRenderer()
    {
        _colorShader->Unbind();
        _indexBuffer->Unbind();
        _vertexBuffer->Unbind();
        OpenGL::DeleteVertexArray(1, &_vao);
    }

    void OpenGLRenderer::Present()
    {
        OpenGL::Finish();
    }

    void OpenGLRenderer::Clear()
    {
        OpenGL::Clear(OpenGL::ClearMask::Color | OpenGL::ClearMask::Depth);
    }

    void OpenGLRenderer::SetClearColor(const Color& color)
    {
        OpenGL::ClearColor(color.R, color.G, color.B, color.A);
    }

    void OpenGLRenderer::BeginFrame()
    {
        _vertexCount = 0;
    }

    void OpenGLRenderer::EndFrame()
    {
        if (_vertexCount > 0)
        {
            OpenGL::BindVertexArray(_vao);
            _indexBuffer->Bind();
            _vertexBuffer->Bind();
            _colorShader->Bind();

            OpenGL::DataType dataType = ToOpenGL(_indexBuffer->Layout().Attributes().Begin()->Kind);
            OpenGL::DrawElements(OpenGL::DrawMode::Triangles, (_vertexCount >> 1) + _vertexCount, dataType, nullptr);
        }
    }

    void OpenGLRenderer::DrawQuad(const Vector2<f32>& position, const Vector2<f32>& size, const Color& color)
    {
        if (_vertexCount >= VertexCount)
        {
            EndFrame();
            BeginFrame();
        }

        Vector2<f32> halfSize = size / 2;

        // clang-format off
        f32 vertices[] =
        {
            position.X - halfSize.X, position.Y - halfSize.Y, color.R, color.G, color.B, color.A,
            position.X - halfSize.X, position.Y + halfSize.Y, color.R, color.G, color.B, color.A,
            position.X + halfSize.X, position.Y - halfSize.Y, color.R, color.G, color.B, color.A,
            position.X + halfSize.X, position.Y + halfSize.Y, color.R, color.G, color.B, color.A,
        };
        // clang-format on

        OpenGL::BindVertexArray(_vao);
        _vertexBuffer->Bind();
        _vertexBuffer->UpdateData(vertices, VertexSize * VertexPerQuad, VertexSize * _vertexCount);

        _vertexCount += VertexPerQuad;
    }
}
