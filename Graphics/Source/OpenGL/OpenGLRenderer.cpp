#include <Ryn/Native/OpenGL.hpp>
#include <Ryn/Native/Platform.hpp>

#include "OpenGL/OpenGLRenderer.hpp"

#include <iostream>

namespace Ryn
{
    OpenGLRenderer::OpenGLRenderer()
    {
        OpenGL::CreateVertexArray(1, &_vao);
        OpenGL::CreateBuffer(1, &_vbo);
        OpenGL::CreateBuffer(1, &_ebo);

        OpenGL::BindVertexArray(_vao);
        OpenGL::BindBuffer(OpenGL::BufferTarget::Array, _vbo);
        OpenGL::BufferData(OpenGL::BufferTarget::Array, VertexSize * VertexCount, nullptr, OpenGL::BufferUsage::DynamicDraw);

        u32 indices[IndexCount];
        for (isize i = 0, j = 0; i < IndexCount; i += IndexPerQuad, j += VertexPerQuad)
        {
            indices[i + 0] = j + 0;
            indices[i + 1] = j + 1;
            indices[i + 2] = j + 2;
            indices[i + 3] = j + 1;
            indices[i + 4] = j + 2;
            indices[i + 5] = j + 3;
        }

        OpenGL::BindBuffer(OpenGL::BufferTarget::ElementArray, _ebo);
        OpenGL::BufferData(OpenGL::BufferTarget::ElementArray, sizeof(indices), indices, OpenGL::BufferUsage::StaticDraw);

        OpenGL::EnableVertexAttribArray(0);
        OpenGL::VertexAttribPointer(0, 2, OpenGL::DataType::Float, false, VertexSize, nullptr);
        OpenGL::EnableVertexAttribArray(1);
        OpenGL::VertexAttribPointer(1, 4, OpenGL::DataType::Float, false, VertexSize, As<void*>(sizeof(f32) * 2));

        char *vertexShaderSource = nullptr, *fragmentShaderSource = nullptr;
        Platform::ReadFile("./Lib/Shaders/Color.vert", vertexShaderSource);
        Platform::ReadFile("./Lib/Shaders/Color.frag", fragmentShaderSource);

        u32 vertexShader = OpenGL::CreateShader(OpenGL::ShaderType::Vertex);
        OpenGL::ShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        OpenGL::CompileShader(vertexShader);

        u32 fragmentShader = OpenGL::CreateShader(OpenGL::ShaderType::Fragment);
        OpenGL::ShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        OpenGL::CompileShader(fragmentShader);

        _shader = OpenGL::CreateProgram();
        OpenGL::AttachShader(_shader, vertexShader);
        OpenGL::AttachShader(_shader, fragmentShader);
        OpenGL::LinkProgram(_shader);

        OpenGL::DeleteShader(vertexShader);
        OpenGL::DeleteShader(fragmentShader);

        delete[] vertexShaderSource;
        delete[] fragmentShaderSource;
    }

    OpenGLRenderer::~OpenGLRenderer()
    {
        OpenGL::BindBuffer(OpenGL::BufferTarget::Array, 0);
        OpenGL::BindBuffer(OpenGL::BufferTarget::ElementArray, 0);
        OpenGL::DeleteBuffer(1, &_ebo);
        OpenGL::DeleteBuffer(1, &_vbo);
        OpenGL::DeleteVertexArray(1, &_vao);
        OpenGL::DeleteProgram(_shader);
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
            OpenGL::BindBuffer(OpenGL::BufferTarget::Array, _vbo);
            OpenGL::BindBuffer(OpenGL::BufferTarget::ElementArray, _ebo);
            OpenGL::UseProgram(_shader);
            OpenGL::DrawElements(OpenGL::DrawMode::Triangles, (_vertexCount >> 1) + _vertexCount, OpenGL::DataType::UnsignedInt, nullptr);
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
        OpenGL::BindBuffer(OpenGL::BufferTarget::Array, _vbo);
        OpenGL::BufferSubData(OpenGL::BufferTarget::Array, VertexSize * _vertexCount, VertexSize * VertexPerQuad, vertices);

        _vertexCount += VertexPerQuad;
    }
}
