
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform float angleY;

out vec3 norm;



void main()
{
    float angleX = 3.1415 / 2.0; //pi/2 radians == 90 degrees
    mat4 transformX = mat4(	1.0,		0,			0,			0,
                        0, 	cos(angleX),	-sin(angleX),		0,
                        0, 	sin(angleX),	 cos(angleX),		0,
                        0, 			0,			  0, 		1);


    mat4 transformY = mat4(	cos(angleY),		0,	  sin(angleY),	   0,
                                    0,	    1.0,  		 0,	       0,
                            -sin(angleY),	0,	  cos(angleY),	   0,
                                    0, 		0,	  		 0,	       1);

    norm = (transformX * vec4(aNorm, 1.0)).xyz;
    vec3 pos = (transformX * vec4(aPos, 1.0)).xyz;

    norm = (transformY * vec4(norm, 1.0)).xyz;
    pos = (transformY * vec4(pos, 1.0)).xyz;

    gl_Position =  vec4(pos.x - 0.5, pos.y - 0.5, pos.z, 1.0);
}
