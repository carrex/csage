#version 330 core

out vec4 fragcolour;

uniform vec4 colour;

void main()
{
    fragcolour = colour;
}
