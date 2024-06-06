#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec2 Pos;

uniform sampler2D screenTexture;

//uniform vec2 screenDims; //Screen width, Screen height

void main()
{

    FragColor = texture(screenTexture, TexCoords);
//    vec4 frag_coord_color = vec4(gl_FragCoord.x/screenDims.x, gl_FragCoord.y/screenDims.y,  0.0, 0.0);
//    FragColor = tex_color + frag_coord_color;


//    FragColor = vec4(0.0, 0.5, 1.0, 1.0);

    if(length(Pos) < 0.1) {
        FragColor = vec4(0.4, 0.4, 0.0, 1.0);
    }

//    vec3 color = vec3(length(Pos));
//    FragColor = vec4(color, 1.0);
}