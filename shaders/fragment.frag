#version 330 core
in vec3 norm;
out vec4 FragColor;

void main() 
{
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // FragColor = vec4(norm, 1.0);
}