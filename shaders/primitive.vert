#version 330 core

layout(location = 0) in vec3 vpos;

uniform mat4 model, view, proj;

void main()
{
    gl_Position = proj * model * view * vec4(vpos, 1.0f);
}
