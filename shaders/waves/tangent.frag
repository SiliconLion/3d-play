#version 330 core
in vec3 norm;
in vec3 pos;

uniform float aTime;

out vec4 FragColor;

void main() { 


    float scale = 0.090;
    // float scale = 1.090;
    float time = aTime;

    // vec3 lightdirection = vec3(0.04, 0.6, 0.3);
    // float shade = dot(lightdirection, norm);

    float shade1 =
        tan( 2 * ( 2.0 *pos.x + pos.y - time * 1.4 )* scale  ) +
        tan(3 * ( pos.x - pos.y - time *0.9 ) * scale) +
        tan(3.7 * (pos.y - 1.3 *pos.x - time + 12.4) * scale) +
        0.5 * tan(1.5 * (pos.y - pos.x - time + 12.4) * scale) +
        0.4 *tan( 10 * (time - 0.9 *pos.x - 1.3 *pos.y + 2.277733) * scale) +
        0.3 *tan(13 * ( pos.x - pos.y - time *0.9 ) * scale) +
        0.4 * tan(14 * (3.3 *pos.y - 1.3 *pos.x - time + 12.4) * scale) +
        0.0
    ;

    float shade2 = 
        // 0.25 * tan(0.2 * (-7.0 * pos.x - 0.3 * pos.y + time + 77.777) * scale) +
        tan(2 * ( 1.4 * pos.x + pos.y + time + 102.224) * scale ) +
        tan(4 * ( -1.9 * pos.x + 2.0 * pos.y + time + 1.111199) * scale) +
        tan(7 * ( 0.4 * pos.x - 0.9* pos.y + time + 4.3232) * scale) +
        tan(20 * ( -0.7 * pos.x - pos.y + time + 6.02377) * scale) +
        0.0
    ;

    float shade3 = 
        tan(1.5 * (pos.x -1.6 *pos.y  + time + 54.23) * scale) +
        tan(6 * (-pos.x + time + 9.83) * scale) +
        tan(9 * (pos.x + 1.2 * pos.y + time + 3.83) * scale) +
        0.0
    ;

    // if(shade1 < 0.2) {shade1 = 0.0;}
    // if(shade2 < 0.2) {shade2 = 0.0;}

    vec3 color1 = vec3(0.1 * shade1, 0.3 * shade1, 0.7 * shade1);
    vec3 color2 = vec3(0.8 * shade2, 0.2 * shade2, 0.2 * shade2);
    vec3 color3 = vec3(0.15 * shade3, 0.9 * shade3, 0.33 * shade3);

    vec3 color = (color1 + color2) + color3;
    // vec3 color = color3;
    FragColor = vec4(color.x, color.y, color.z, 1.0);
}