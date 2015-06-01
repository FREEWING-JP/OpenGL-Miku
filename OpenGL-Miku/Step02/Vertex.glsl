#version 450

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color_in;

out vec3 color;

void main()
{
    color = color_in;
    gl_Position = vec4(position, 0.0, 1.0);
}
