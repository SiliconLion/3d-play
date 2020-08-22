#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
uniform float time;

out vec3 pos;
out vec3 norm;

// vec3 normalize(vec3 vector) {
//     float measure = sqrt(
//         pow(vector.x, 2) + pow(vector.y, 2), pow(vector.z, 2)
//     );
//     vec3 normalized = vec3(vector.x / measure, vector.y/measure, vector.z /measure);
//     return normalized;
// }

void main() {
    // float delta = sin(time + aPos.x);
    // pos = vec3(aPos.x, aPos.y, aPos.z + delta);

    //figure out how to update this correctly 
    norm = aNorm;
    pos = aPos;

    gl_Position = vec4(pos, 1.0);
}