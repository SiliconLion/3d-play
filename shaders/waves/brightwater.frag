#version 330 core
in vec3 norm;
in vec3 pos;

uniform float aTime;

out vec4 FragColor;

float distance(float x1, float y1, float x2, float y2) {
    return sqrt( pow(x1 - x2, 2) + pow(y1 -y2, 2) );
}

//distance from the fragment to a point p, with px and py being x and y components respectively.
float dist_from(float px, float py) {
    return distance(px,py, pos.x, pos.y);
}

void main() { 


    float scale = 0.40;
    float time = 0.2 * aTime;

    // vec3 lightdirection = vec3(0.04, 0.6, 0.3);
    // float shade = dot(lightdirection, norm);

    float shade =
        0.5 * sin( 9 * ( dist_from(-1,0)- time + 16.2) * scale ) +
        sin( 16 * ( dist_from(2,2.6)- time - 4.2) * scale ) +
        0.7 *sin(11 * ( dist_from(20,2.6)- time  + 6.3) * scale ) +
        0.3 * sin( 30 * ( dist_from(-0.5,-1.6)- time ) * scale ) +
        0.5 * sin( 10 * ( dist_from(1.9,0)- time) * scale ) +
        0.0
    ;


    time = 1.9 * time;
    //small ripples
    shade = shade + 
        0.3 * sin( 120 * (dist_from(1.2, -7) - time) * scale) +
        0.2 * sin( 240 * (dist_from(0.4, -12.37) - time +33.2) * scale) +
        0.05 * sin( 680 * (dist_from(1.5, -9) - time +33.2) * scale) +
        // 0.02 
        0.0
    ;

    time = 1.5 * time;

    shade = shade +
        //small ripples in other direction
        0.2 * sin( 120 * (dist_from(1.9, -0.8) - time ) * scale) +
        0.1 * sin( 240 * (dist_from(1.1, -1.8) - time +3.552) * scale) +
        0.05 * sin( 680 * (dist_from(0.9, -2.8) - time +3.552) * scale) +
        0.0
    ;

    //invert comments/code for darkmode/lightmode --------

    if(shade < 0.4) {shade = 0.0;}

    if(shade < 0.9) {shade = 0.0;}
    if(shade > 1.0) {shade = 1.0;}

    // vec3 color =  vec3(0.1 * shade, 0.3 * shade, 0.7 * shade);
    vec3 color = (shade * 0.8 * vec3(0.9, 0.8, 0.7) ) + vec3(0.1, 0.2, 0.3);
    //--------------------
    FragColor = vec4(color.x, color.y, color.z, 1.0);
}