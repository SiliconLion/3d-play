#pragma once
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    // #include <OpenGL/gl3ext.h>
    #include <GLFW/glfw3.h>
#endif

#include <stdlib.h>
#include "stlreader.h"

//each vertex consists of 6 floats. The first 3 for position, then next 3 for normal
const int VERTEX_SIZE = 6 * sizeof(float); 

typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    // unsigned int EBO;
    
    //the number of verticies `verticies` can hold
    int verticies_capacity;
    int verticies_count;
    float * verticies;
    //what mode the vertex buffer associated with VBO is. 
    //eg, GL_STATIC_DRAW, GL_DYNAMIC_DRAW
    GLenum usage;

} Geometry;

//usage denotes the hint to be given for how the vertex buffer object will
//be used. should be one of GL_STREAM_DRAW, GL_STREAM_READ, 
//GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, 
//GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY
Geometry * geom_new(GLenum usage) {
    Geometry * geom = calloc(1, sizeof(Geometry));

    

    geom->verticies_count = 0;
    //this is an arbitrary initial capacity
    geom->verticies_capacity = 1 << 8;
    geom->verticies = calloc(geom->verticies_capacity, VERTEX_SIZE);

    geom->usage = usage;

    glGenVertexArrays(1, &(geom->VAO) );
    glBindVertexArray(geom->VAO);

    glGenBuffers(1, &(geom->VBO) );
    glBindBuffer(GL_ARRAY_BUFFER, geom->VBO);

    glBufferData(GL_ARRAY_BUFFER, geom->verticies_capacity * VERTEX_SIZE, NULL, usage);

    //sets up the position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*) 0);
    glEnableVertexAttribArray(0);
    //sets up the normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //unbinds so we dont interfere with other state
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return geom;
}

void geom_bind(Geometry * geom) {
    glBindVertexArray(geom->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, geom->VBO);
}

void geom_unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//data is the new array of floats for verticies, and vertex_count is the number
//of verticies it contains
void geom_replace_verticies(Geometry* geom, float * data, int vertex_count) {
    geom_bind(geom);

    //copy data into geom->verticies
    geom->verticies = realloc(geom->verticies, vertex_count * VERTEX_SIZE);
    memcpy(geom->verticies, data, vertex_count * VERTEX_SIZE);

    glBufferData(GL_ARRAY_BUFFER, vertex_count * VERTEX_SIZE, geom->verticies, geom->usage);

    geom->verticies_count = vertex_count;

    geom_unbind();
}



Geometry * geom_from_stl(const char * path) {
    stl_obj * obj = stl_from_file(path);
    if(obj == NULL) {return NULL;}

    stl_normalize(obj, 1.0);


    //3 verticies per triangle.
    float * vert_data = calloc(obj->tri_count * 3, VERTEX_SIZE);


    float * curpos = vert_data;
    for(int i = 0; i < obj->tri_count; i++) {
        for (int j = 0; j < 3; j++) {

            //copy the j'th vertex in the i'th triangle to curpos
            memcpy(curpos, obj->tris[i].verts[j], sizeof(float) * 3);
            curpos += 3;

            memcpy(curpos, obj->tris[i].norm, sizeof(float) * 3);
            curpos += 3;
        }
    }

    Geometry * geom = geom_new(GL_STATIC_DRAW);

    geom_replace_verticies(geom, vert_data, obj->tri_count * 3);

    free(vert_data);

    return geom;
}

void geom_draw(Geometry * geom) {
    glEnable(GL_DEPTH_TEST);  
    geom_bind(geom);

    glDrawArrays(GL_TRIANGLES, 0, geom->verticies_count);

    geom_unbind();
}
