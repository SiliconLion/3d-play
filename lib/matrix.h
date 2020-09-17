#pragma once

#include <string.h>
#include <stdbool.h>
#include "utilities.h"

//3x3 array
typedef struct {
    //the elements of the matrix stored as a flat array. 
    float elements[9];
} mat_3x3; 

// #define MAT_3X3_ZERO (mat_3x3) {.elements = \
//                     {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}}

const mat_3x3 MAT_3X3_ZERO = {.elements = 
                    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};

const mat_3x3 MAT_3X3_IDENT = {.elements = 
                    {1.0, 0.0, 0.0,   0.0, 1.0, 0.0,   0.0, 0.0, 1.0}};

//returns whether the matricies are equal or not
bool mat_3x3_equal(mat_3x3 lhs, mat_3x3 rhs) {
    int cmp = memcmp(lhs.elements, rhs.elements, sizeof(float) * 9);
    if (cmp == 0) {
        return true;
    } else {
        return false;
    }
}

//does not take ownership of elements. copies it instead
mat_3x3 mat_3x3_new(float elements[9]) {
    mat_3x3 matrix;
    //we dont have to allocate elements first because its stack allocated already
    memcpy(matrix.elements, elements, sizeof(float) * 9);
    return matrix;
}


//gets the value of an element of a 3x3 matrix
float mat_3x3_get( mat_3x3 matrix, int row, int col) {
    return matrix.elements[util_flatten_index(row, col, 3)];
}


void mat_3x3_get_row(float dest[3], mat_3x3 matrix, int row) {
    memcpy(dest, matrix.elements + row * 3, sizeof(float) * 3);
}

void mat_3x3_get_col(float dest[3], mat_3x3 matrix, int col) {
    dest[0] = matrix.elements[col];
    dest[1] = matrix.elements[col + 3];
    dest[2] = matrix.elements[col + 6];
}

void mat_3x3_set(mat_3x3 * matrix, float value, int row, int col) {
    unsigned int i = util_flatten_index(row, col, 3);
    matrix->elements[i] = value;
}

mat_3x3 mat_3x3_add(mat_3x3 lhs, mat_3x3 rhs) {
    mat_3x3 matrix = MAT_3X3_ZERO;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            float lhs_element = mat_3x3_get(lhs, row, col);
            float rhs_element = mat_3x3_get(rhs, row, col);
            mat_3x3_set(&matrix, lhs_element + rhs_element, row, col);
        }
    }
    return matrix;
}

//multiplty two 3x3 matricies. 
mat_3x3 mat_3x3_mult(mat_3x3 lhs, mat_3x3 rhs) {

    mat_3x3 matrix = MAT_3X3_ZERO;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            float lhsrow[3], rhscol[3];
            mat_3x3_get_row(lhsrow, lhs, row);
            mat_3x3_get_col(rhscol, rhs, col);


            float element = 0;
            for ( int i = 0; i < 3; i++) {
                element += lhsrow[i] * rhscol[i];
            }

            mat_3x3_set(&matrix, element, row, col);
        }
    }
    return matrix;
}