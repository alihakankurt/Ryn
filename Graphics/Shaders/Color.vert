#version 410 core

layout (location = 0) in vec2 iPosition;
layout (location = 1) in vec4 iColor;

out vec4 vColor;

void main()
{
    vColor = iColor;
    gl_Position = vec4(iPosition, 0.0, 1.0);
}
