#version 330 core
in vec3 norm;
in vec3 pos;

uniform float time;

out vec4 FragColor;

void main() { 

    float scale = 1.0;

    // vec3 lightdirection = vec3(0.04, 0.6, 0.3);
    // float shade = dot(lightdirection, norm);

    float shade =
        sin(time * scale) +
        cos(2 * (pos.y+ time + 1.232324 )* scale) +
        sin(  3 * (pos.x +  0.3 *pos.y + time) * scale) +
        sin(  6* (pos.x + pos.y + time) * scale ) +
        0.4 * sin(14.0 * ( 0.2 * pos.x + pos.y + time * 1.3 ) * scale )
    ;

    //invert comments/code for darkmode/lightmode --------

    if(shade < 0.4) {shade = 0.0;}

    // if(shade < 0.9) {shade = 0.0;}
    // if(shade > 1.0) {shade = 1.0;}

    vec3 color =  vec3(0.1 * shade, 0.3 * shade, 0.7 * shade);
    // vec3 color = (shade * 0.8 * vec3(0.9, 0.8, 0.7) ) + vec3(0.1, 0.2, 0.3);
    //--------------------
    FragColor = vec4(color.x, color.y, color.z, 1.0);
}

