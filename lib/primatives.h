#pragma once

#include "geometry.h"
#include "utilities.h"





//Returns a Geometry that is a flat triangular mesh with dimensions width, height. 
//the mesh is divided into rectangles 
//with w_resolution number of rectangles across the width, and 
//h_resolution number of rectangles across the height.
//then each rectangle has it's diagonal connected to make them tris. 
//Orientation is along the x and y plane
//usage is a paramater passed to the geometry constructor telling it how it's vertex buffer will be used.
//see Geometry in geometry.h to see whats allowed. 
Geometry * prim_new_plane(float width, float height, int w_resolution, int h_resolution, GLenum usage) {
 
    int rect_count = w_resolution * h_resolution;

    //the grid dimensions of the vertices. Just clustring the logically related variables.
    //total number of points in the grid, the number of points width-wise, and height-wise
    struct {
        int total_count;
        int w_count;
        int h_count;
    } griddims = {
        (w_resolution +1)  * (h_resolution +1),
        (w_resolution +1),
        (h_resolution +1)
    };
    
    float w_start = 0.0 - (width / 2);
    float h_start = 0.0 - (height / 2);

    float w_step = width / (float)w_resolution;
    float h_step = height / (float)h_resolution;

    //formatted such that 3 consecutive floats form an (x,y,z) coordinate
    float * positions = calloc(griddims.total_count, sizeof(float) * 3);
    //pointer used to walk along positions
    float * pos_walker = positions;

    for(int row = 0; row < griddims.h_count; row++) {
        for(int col = 0; col < griddims.w_count; col++) {
            *pos_walker = w_start + ((float)col * w_step); 
            pos_walker++;
            *pos_walker = h_start + ((float)row * h_step);
            pos_walker++;
            *pos_walker = 0.0;
            pos_walker++;
        }
    }

    int vertex_count = rect_count * 2 * 3;

    //the order in which we will copy the positions into verticies in order to make triangles.
    //if in the future Geometry supports indexing, may want to change this to an `unsigned int *`. 
    int * indicies = calloc(vertex_count, sizeof(int));
    //pointer used to walk along indicies
    int * ind_walker = indicies;

    
    //steps over each row and column except the last of each, and generates indicies of 2 triangles 
    //starting at the bottom left and top right respectively, with counter clockwise winding. 
    for(int row = 0; row < griddims.h_count - 1; row++) {
        for(int col = 0; col < griddims.w_count - 1; col++) {
            //first tri
            *ind_walker = (int)util_flatten_index(row, col, griddims.w_count);
            ind_walker++;
            *ind_walker = (int)util_flatten_index(row, col + 1, griddims.w_count);
            ind_walker++;
            *ind_walker = (int)util_flatten_index(row + 1, col + 1, griddims.w_count);
            ind_walker++;

            //second tri
            *ind_walker = (int)util_flatten_index(row + 1, col + 1, griddims.w_count);
            ind_walker++;
            *ind_walker = (int)util_flatten_index(row +1, col, griddims.w_count);
            ind_walker++;
            *ind_walker = (int)util_flatten_index(row, col, griddims.w_count);
            ind_walker++;
        }
    }

    //should probably assert that VERTEX_SIZE = sizeof(float) * 6
    //properly formatted verticies for Geometry
    float * verticies = calloc(vertex_count, VERTEX_SIZE);
    //pointer used to walk along verticies
    float * vert_walker = verticies;

    //since all the tris are coplaner, they share a normal
    float normal[3] = {0.0, 0.0, 1.0};

    for(int i = 0; i < vertex_count; i++) {
        //since each position takes 3 floats, we have to step by 3. Hence `indicies[i] * 3`.
        memcpy(vert_walker, positions + (indicies[i] * 3), sizeof(float) * 3);
        vert_walker += 3;
        memcpy(vert_walker, normal, sizeof(float) * 3);
        vert_walker += 3; 
    }


    Geometry * geom = geom_new(usage);
    geom_replace_verticies(geom, verticies, vertex_count);

    free(positions);
    free(indicies);
    free(verticies);

    return geom;
}
