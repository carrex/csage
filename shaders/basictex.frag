#version 330 core

in vec3 colour;
in vec2 texcoord;

out vec4 FragColor;

uniform sampler2D ourtex;

void main()
{
    FragColor = texture(ourtex, texcoord) * vec4(colour, 1.0);
}
