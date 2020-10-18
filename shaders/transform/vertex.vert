#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4x4 transformation;

// out vec3 pos;
out vec3 norm;

void main() {
    norm = aNorm;
    gl_Position = transformation * vec4(aPos, 1.0);
}