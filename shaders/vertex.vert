
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 norm;

void main()
{
    norm = aNorm;
    gl_Position = 0.003 *vec4(aPos, 1.0);
}