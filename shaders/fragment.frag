#version 330 core
in vec3 norm;

// uniform vec3 lighting;

out vec4 FragColor;


void main() 
{
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);

    vec3 lighting = 1.5 * vec3(-0.3, 0.3, -0.2);

    float shadow = dot(lighting, norm);
    vec3 green = vec3(0.5, 0.8, 0.6);
    vec3 shaded_green = shadow * green;
    FragColor = vec4(shaded_green, 1.0);
    // FragColor = vec4(norm, 1.0);
}