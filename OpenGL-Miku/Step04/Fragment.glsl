#version 450

in vec4 position;
in vec3 normal;
in vec2 uv;

uniform sampler2D texl;

out vec4 out_color;

void main()
{
    vec4 light = vec4(0.0, 2.0, 4.0, 1.0);
    vec3 s = normalize(vec3(light - position));
    vec3 diffusion = vec3(1.0, 1.0, 1.0) * max(dot(s, normal), 0.0);
    vec3 material = texture2D(texl, uv).rgb;
    out_color = vec4(diffusion * material, 1.0);
}
