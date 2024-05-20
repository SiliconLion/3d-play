#version 330 core

in vec2 TexCoords;

//uniform float aTime;
//
//uniform vec3 aMetaball; //x, y, radius.
//// uniform float aZoom;
//
out vec4 FragColor;
//
//float dist(vec2 a, vec2 b) {
//    return sqrt( (a.x + b.x)* (a.x + b.x)  + (a.y + b.y)* (a.y + b.y) );
//}
//
//float scale = 1.0 / 10.0;

void main() {
//    vec3 scaled_ball = scale * aMetaball;
//    vec3 scaled_pos = pos;
//
//
//    float dist_from_center = dist(scaled_ball.xy, scaled_pos.xy);
//    float radius = scaled_ball.z;
//    if(dist_from_center < radius) {
//        float shade = 1.0 - dist_from_center;
////        FragColor = vec4(shade, shade, shade, 1.0);
//        FragColor = vec4(0.0, 0.0, 1.0, 1.0);
//    } else {
////        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
//        FragColor = vec4(0.0, 0.0, 0.0, 0.0); //transparent
//    }


//    FragColor = vec4(0.1, 0.6, 0.1, 1.0);
//    FragColor = vec4(1., 1., 1., 1.);

//    vec2 frag_coords = (2.0 * gl_FragCoord.xy ) + vec2(-1, 0.);
//    float dist_from_center = dist(frag_coords, vec2(0., 0.));
//    if(dist_from_center < 0.4) {
//        FragColor = vec4(1.0,0.4,0.5,1.0);
//    } else {
//        FragColor = vec4(0.0,1.0,0.0,1.0);
//    }

    FragColor = vec4(TexCoords.x, TexCoords.y, 0.0, 1.0);

}

