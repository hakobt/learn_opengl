#version 410 core

layout (location = 0) in vec3 aPos;

out vec4 bul;

void main()
{
    bul = vec4(aPos, 1.0);
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}