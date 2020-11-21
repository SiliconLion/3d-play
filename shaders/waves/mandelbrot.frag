#version 330 core
in vec3 norm;
in vec3 pos;

uniform float aTime;
uniform vec2 aDimensions;

in vec4 gl_FragCoord;
out vec4 FragColor;

#define product(a, b) vec2(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x)
// #define conjugate(a) vec2(a.x,-a.y)
// #define divide(a, b) vec2(((a.x*b.x+a.y*b.y)/(b.x*b.x+b.y*b.y)),((a.y*b.x-a.x*b.y)/(b.x*b.x+b.y*b.y)))

//the .x component of the return is either 0 or 1. 0 if it doesn't go over the threshold, 1 if it does. 
vec3 mandelbrot(float x, float y, int iterations, float threshold) {
    vec2 c = vec2(x, y);
    vec2 z = vec2(0, 0);
    vec2 speed = vec2(0,0);

    float escaped = 0.0;
    for(int i = 0; i < iterations; i++) {
        z = product(z, z) + c;
        if (abs(z.x) > threshold) {
            speed.x = float(i);
            escaped = 1.0; 
            break;
        } else if( abs(z.y) > threshold) {
            speed.y = float(i);
            escaped = 1.0; 
            break;
        }
    }
    return vec3(escaped, z);
}

void main() { 
    float width = aDimensions[0];
    float height = aDimensions[1];

    float x = gl_FragCoord.x / width / 2;
    float y = gl_FragCoord.y / height / 2;

    vec3 speed = mandelbrot(x, y, int(aTime * 2), 5000.0);
    if(speed.x == 1.0) {
        FragColor = vec4(speed.y, speed.z, 1.0, 1.0);
    } else {
        FragColor = vec4(0,0,0,1.0);
    }

}