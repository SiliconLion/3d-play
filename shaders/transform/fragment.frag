
#version 330 core
in vec3 norm;

uniform sampler2D matcap;

out vec4 FragColor;

void main() {
    vec2 matcapPos = vec2( (norm.x / 1.0) + 0.5, (norm.y / 1.0) + 0.5);
    FragColor = texture(matcap, matcapPos);
}