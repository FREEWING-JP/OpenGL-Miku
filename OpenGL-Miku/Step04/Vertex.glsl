#version 450

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;

uniform mat4 mv_matrix;
uniform mat3 normal_matrix;
uniform mat4 mvp;

out vec4 position;
out vec3 normal;
out vec2 uv;

void main()
{
    uv = in_uv;
    normal = normalize(normal_matrix * in_normal);
    position = mv_matrix * vec4(in_position, 1.0);

    gl_Position = mvp * vec4(in_position, 1.0);
}
