#version 410 core

in vec4 bul;
out vec4 FragColor;

uniform float uMultiplier;

void main()
{
    FragColor = (1 - bul) * clamp(uMultiplier, 0.2, 1.0);
}