#version 330 core

layout(location = 0) in vec3 vpos;
layout(location = 1) in vec2 tpos;

out vec2 TPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(vpos, 1.0);
    TPos        = tpos;
}
