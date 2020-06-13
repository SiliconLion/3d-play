#version 330 core
in vec3 norm;

// uniform vec3 lighting;

out vec4 FragColor;


void main() 
{
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0);

    vec3 lighting = 1.5 * vec3(-0.3, 0.3, -0.2);

    float shadow = dot(lighting, norm);
    FragColor = vec4(shadow, shadow, shadow, 1.0);
    // FragColor = vec4(norm, 1.0);
}