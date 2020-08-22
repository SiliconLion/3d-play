#version 330 core
in vec3 norm;
in vec3 pos;

uniform float time;

out vec4 FragColor;

void main() { 
    // vec3 lightdirection = vec3(0.04, 0.6, 0.3);
    // float shade = dot(lightdirection, norm);

    float shade = 
        sin(time) +
        sin(  3 * (pos.x +  0.3 *pos.y + time) ) +
        sin(  6* (pos.x + pos.y + time) ) +
        0.4 * sin(14.0 * ( 0.2 * pos.x + pos.y + time * 1.3 ) )
    ;
    vec3 color =  vec3(0.1 * shade, 0.3 * shade, 0.7 * shade);
    FragColor = vec4(color.x, color.y, color.z, 1.0);
    // FragColor = vec4(0.2, 0.2, 0.2, 0.2);
}

