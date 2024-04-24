#ifndef __RYN_NATIVE_OPENGL_HPP__
#define __RYN_NATIVE_OPENGL_HPP__

#include <Ryn/Core.hpp>
#include <Ryn/Native/Platform.hpp>

namespace Ryn
{
    class OpenGL
    {
      public:
        enum struct ClearMask : u32
        {
            Color = 0x0000'4000,
            Depth = 0x0000'0100,
            Stencil = 0x0000'0400
        };

        enum struct BufferTarget : u32
        {
            Array = 0x8892,
            AtomicCounter = 0x92C0,
            CopyRead = 0x8F36,
            CopyWrite = 0x8F37,
            DispatchIndirect = 0x90EE,
            DrawIndirect = 0x8F3F,
            ElementArray = 0x8893,
            PixelPack = 0x88EB,
            PixelUnpack = 0x88EC,
            Query = 0x9192,
            ShaderStorage = 0x90D2,
            Texture = 0x8C2A,
            TransformFeedback = 0x8C8E,
            Uniform = 0x8A11
        };

        enum struct BufferUsage : u32
        {
            StreamDraw = 0x88E0,
            StreamRead = 0x88E1,
            StreamCopy = 0x88E2,
            StaticDraw = 0x88E4,
            StaticRead = 0x88E5,
            StaticCopy = 0x88E6,
            DynamicDraw = 0x88E8,
            DynamicRead = 0x88E9,
            DynamicCopy = 0x88EA
        };

        enum struct DrawMode : u32
        {
            Points = 0x0000,
            Lines = 0x0001,
            LineLoop = 0x0002,
            LineStrip = 0x0003,
            Triangles = 0x0004,
            TriangleStrip = 0x0005,
            TriangleFan = 0x0006,
            LinesAdjacency = 0xA,
            LineStripAdjacency = 0xB,
            TrianglesAdjacency = 0xC,
            TriangleStripAdjacency = 0xD,
            Patches = 0xE
        };

        enum struct DataType : u32
        {
            Byte = 0x1400,
            UnsignedByte = 0x1401,
            Short = 0x1402,
            UnsignedShort = 0x1403,
            Int = 0x1404,
            UnsignedInt = 0x1405,
            Float = 0x1406,
            Double = 0x140A
        };

        enum struct ShaderType : u32
        {
            Vertex = 0x8B31,
            Fragment = 0x8B30,
            Geometry = 0x8DD9,
            TessControl = 0x8E88,
            TessEvaluation = 0x8E87,
            Compute = 0x91B9
        };

      public:
        using ClearFunction = void (*)(ClearMask mask);
        static ClearFunction Clear;

        using ClearColorFunction = void (*)(f32 red, f32 green, f32 blue, f32 alpha);
        static ClearColorFunction ClearColor;

        using CreateVertexArrayFunction = void (*)(u32 n, u32* arrays);
        static CreateVertexArrayFunction CreateVertexArray;

        using DeleteVertexArrayFunction = void (*)(u32 n, const u32* arrays);
        static DeleteVertexArrayFunction DeleteVertexArray;

        using BindVertexArrayFunction = void (*)(u32 array);
        static BindVertexArrayFunction BindVertexArray;

        using CreateBufferFunction = void (*)(u32 n, u32* buffers);
        static CreateBufferFunction CreateBuffer;

        using DeleteBufferFunction = void (*)(u32 n, const u32* buffers);
        static DeleteBufferFunction DeleteBuffer;

        using BindBufferFunction = void (*)(BufferTarget target, u32 buffer);
        static BindBufferFunction BindBuffer;

        using BufferDataFunction = void (*)(BufferTarget target, isize size, const void* data, BufferUsage usage);
        static BufferDataFunction BufferData;

        using BufferSubDataFunction = void (*)(BufferTarget target, isize offset, isize size, const void* data);
        static BufferSubDataFunction BufferSubData;

        using EnableVertexAttribArrayFunction = void (*)(u32 index);
        static EnableVertexAttribArrayFunction EnableVertexAttribArray;

        using VertexAttribPointerFunction = void (*)(u32 index, i32 size, DataType type, bool normalized, isize stride, const void* pointer);
        static VertexAttribPointerFunction VertexAttribPointer;

        using CreateProgramFunction = u32 (*)();
        static CreateProgramFunction CreateProgram;

        using DeleteProgramFunction = void (*)(u32 program);
        static DeleteProgramFunction DeleteProgram;

        using LinkProgramFunction = void (*)(u32 program);
        static LinkProgramFunction LinkProgram;

        using UseProgramFunction = void (*)(u32 program);
        static UseProgramFunction UseProgram;

        using CreateShaderFunction = u32 (*)(ShaderType type);
        static CreateShaderFunction CreateShader;

        using DeleteShaderFunction = void (*)(u32 shader);
        static DeleteShaderFunction DeleteShader;

        using AttachShaderFunction = void (*)(u32 program, u32 shader);
        static AttachShaderFunction AttachShader;

        using CompileShaderFunction = void (*)(u32 shader);
        static CompileShaderFunction CompileShader;

        using ShaderSourceFunction = void (*)(u32 shader, u32 count, char** string, const i32* length);
        static ShaderSourceFunction ShaderSource;

        using DrawElementsFunction = void (*)(DrawMode mode, isize count, DataType type, const void* indices);
        static DrawElementsFunction DrawElements;

        using FinishFunction = void (*)();
        static FinishFunction Finish;

      private:
        static Platform::Module Handle;

      public:
        static bool Load();
        static void Unload();
    };
}

#endif