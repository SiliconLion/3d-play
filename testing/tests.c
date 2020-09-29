#include <stdbool.h>
#include <stdio.h>
#include "matrix.h"

#define RESET   "\033[0m"
#define GREEN   "\033[32m" 
#define RED     "\033[31m"  

#define TESTSUCCESS \
    printf(GREEN "Test Succeeded: %s%s%s", __func__, RESET, "\n");\
    return true

#define TESTFAILED \
    printf(RED "Test Failed: %s%s%s", __func__, RESET, "\n");\
    return false

#define TESTISTRUE(X) \
        if ( (X) == true) { \
            TESTSUCCESS; \
        } else { \
            TESTFAILED; \
        } 


bool test_mat_3x3_equal() {
    mat_3x3 control = {.elements = 
                {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}};
    mat_3x3 ctrlcopy = {.elements = 
                {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}};
    mat_3x3 different = {.elements = 
                {0.0, 12.0, 8.0, -5.0, 5.0, 7.0, 7.0, 15.0, 9.0}};

    bool equal = mat_3x3_equal(control, ctrlcopy); 
    if (equal == false) {
        TESTFAILED;
    }
    
    equal = mat_3x3_equal(control, different); 
    if(equal == true) {TESTFAILED;}

    TESTSUCCESS;

}

bool test_mat_3x3_new() {
    mat_3x3 control = {.elements = 
                {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0}};

    float a[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};           
    mat_3x3 new = mat_3x3_new(a);
    TESTISTRUE(mat_3x3_equal(control, new));
}

bool test_mat_3x3_predefined_matrices() {
    mat_3x3 zero = {.elements = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}}; 
    mat_3x3 identity = {.elements = {1.0, 0.0, 0.0,   0.0, 1.0, 0.0,   0.0, 0.0, 1.0}};
    bool correct = true;
    correct &= mat_3x3_equal(zero, MAT_3X3_ZERO);
    correct &= mat_3x3_equal(identity, MAT_3X3_IDENT);
    TESTISTRUE(correct);
}

bool test_mat_3x3_get() {
    mat_3x3 control = {.elements = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};
    
    bool correct = true;
    for(int r =0; r < 3; r++) {
        for(int c = 0; c < 3; c++) {
            correct &= ( 
                (float)( (r * 3) + c) == mat_3x3_get(control, r, c));
        }
    }
    TESTISTRUE(correct);
}

bool test_mat_3x3_get_row() {
    mat_3x3 control = {.elements = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};
    bool correct = true;
    for(int r = 0; r< 3; r++) {
        float row[3]; 
        mat_3x3_get_row(row, control, r);
        for(int i = 0; i < 3; i++) {
            correct &= (row[i] == (float)( (r *3) + i) );
        }
    }
    TESTISTRUE(correct);
}

bool test_mat_3x3_get_col() {
    mat_3x3 control = {.elements = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};
    bool correct = true;
    for(int c = 0; c < 3; c++) {
        float col[3];
        mat_3x3_get_col(col, control, c);
        for(int i = 0; i < 3; i++) {
            correct &= (col[i] == (float)( (i*3) + c ) );
        }
    }
    TESTISTRUE(correct);
}

bool test_mat_3x3_set() {
    mat_3x3 control = {.elements = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};
    mat_3x3 set_matrix = MAT_3X3_ZERO;
    for(int r = 0; r< 3; r++) {
        for(int c =0; c< 3; c++) {
            mat_3x3_set(&set_matrix, (float)( (r*3) + c ), r, c);
        }
    }
    TESTISTRUE(mat_3x3_equal(control, set_matrix));
}

bool test_mat_3x3_add() {
    mat_3x3 control = {.elements = {8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0}};
    mat_3x3 accending = {.elements = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};
    mat_3x3 decending = {.elements = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0}};

    TESTISTRUE(mat_3x3_equal(control, mat_3x3_add(accending, decending)));
}

bool test_mat_3x3_negate() {
    mat_3x3 control = {.elements = {-0.0, -1.0, -2.0, -3.0, -4.0, -5.0, -6.0, -7.0, -8.0}};
    mat_3x3 matrix = {.elements = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};

    TESTISTRUE(mat_3x3_equal(control, mat_3x3_negate(matrix)) );
}

bool test_mat_3x3_sub() {
    mat_3x3 control = {.elements = {  6.0,  6.0,  6.0,  6.0,  6.0,  6.0,  6.0,  6.0,  6.0}};
    mat_3x3 lhs = {.elements = { 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0}};
    mat_3x3 rhs = {.elements = {  4.0,  4.0,  4.0,  4.0,  4.0,  4.0,  4.0,  4.0,  4.0}};

    mat_3x3 difference = mat_3x3_sub(lhs, rhs);

    TESTISTRUE( mat_3x3_equal(control, difference));
}

bool test_mat_3x3_mult() {
    mat_3x3 accending = {.elements = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}};
    mat_3x3 decending = {.elements = {8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0}};
    
    bool correct = true;

    correct &= mat_3x3_equal(accending, mat_3x3_mult(accending, MAT_3X3_IDENT)) ;
    correct &= mat_3x3_equal(MAT_3X3_ZERO, mat_3x3_mult(decending, MAT_3X3_ZERO)) ;

    mat_3x3 control1 = {.elements = {9.0, 6.0, 3.0, 54.0, 42.0, 30.0, 99.0, 78.0, 57.0}};

    correct &= mat_3x3_equal(control1, mat_3x3_mult(accending, decending)) ;

    mat_3x3 control2 = {.elements = {57.0, 78.0, 99.0, 30.0, 42.0, 54.0, 3.0, 6.0, 9.0}};

    correct &= mat_3x3_equal(control2, mat_3x3_mult(decending, accending)) ;

    TESTISTRUE(correct);
}


//Tests for 4x4 matrices 

bool test_mat_4x4_equal() {
    mat_4x4 control = {.elements ={
        0.0, 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0, 7.0,
        8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    }};

    mat_4x4 ctrlcopy = {.elements ={
        0.0, 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0, 7.0,
        8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    }};

    mat_4x4 different = {.elements ={
        10.0, 11.0, 21.0, 33.0,
        0.0, 5.0, 64.0, 7.0,
        0.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    }};

    bool correct = true;
    correct &= mat_4x4_equal(control, ctrlcopy);
    correct &= !( mat_4x4_equal(control, different) );

    TESTISTRUE(correct);
}

bool test_mat_4x4_new() {
    mat_4x4 control = {.elements ={
        0.0, 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0, 7.0,
        8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    }};

    float elements[16] = {
        0.0, 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0, 7.0,
        8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    };

    mat_4x4 new = mat_4x4_new(elements);
    TESTISTRUE( mat_4x4_equal(control, new));
}

bool test_mat_4x4_predefined_matrices() {
    mat_4x4 zero = {.elements = {
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0
    }};

    mat_4x4 identity = {.elements = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    }};

    bool correct = true; 
    correct &= mat_4x4_equal(zero, MAT_4x4_ZERO);
    correct &= mat_4x4_equal(identity, MAT_4X4_IDENT);

    TESTISTRUE(correct);
}

bool test_mat_4x4_get() {
    mat_4x4 control = {.elements ={
        0.0, 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0, 7.0,
        8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    }};

    bool correct = true;

    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            float element = mat_4x4_get(control, row, col);
            correct &= (element == util_flatten_index(row, col, 4));
        }
    }

    TESTISTRUE(correct);
}

bool test_mat_4x4_get_row() {
    mat_4x4 control = {.elements ={
        0.0, 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0, 7.0,
        8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    }};

    bool correct = true;

    for(int i = 0; i < 4; i++) {
        float control_row[4];
        for(int j = 0; j < 4; j++) {
            int start = i * 4; 
            control_row[j] = j + (float)start;
        }

        float row[4];
        mat_4x4_get_row(row, control, i);

        //returns 0 if they are equal. so invert that to make it a bool
        bool equal = !(memcmp(row, control_row, sizeof(float) * 4) );
        correct &= equal; 
    }

    TESTISTRUE(correct);
}

bool test_mat_4x4_get_col() {
    mat_4x4 control = {.elements ={
        0.0, 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0, 7.0,
        8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    }};

    bool correct = true;

//each column in the matrix
    for(int i = 0; i < 4; i++) {
        float control_col[4];
        //each row in the column
        for(int j = 0; j < 4; j++) {
            control_col[j] = (j * 4) + i;
        }

        float col[4];
        mat_4x4_get_col(col, control, i);

        //returns 0 if they are equal. so invert that to make it a bool
        bool equal = !(memcmp(col, control_col, sizeof(float) * 4) );
        correct &= equal; 
    }

    TESTISTRUE(correct);
}

bool test_mat_4x4_set() {
    mat_4x4 control = {.elements ={
        0.0, 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0, 7.0,
        8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    }};

    mat_4x4 set_matrix = MAT_4x4_ZERO;
    
    for(int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            mat_4x4_set(
                    &set_matrix, 
                    util_flatten_index(row, col, 4), 
                    row, col);
        }
    }

    TESTISTRUE( mat_4x4_equal(control, set_matrix) );
}

bool test_mat_4x4_add() {
    mat_4x4 control = {.elements = { 
        15.0, 15.0, 15.0, 15.0,
        15.0, 15.0, 15.0, 15.0,
        15.0, 15.0, 15.0, 15.0,
        15.0, 15.0, 15.0, 15.0
    }};

    mat_4x4 accending = {.elements ={
        0.0, 1.0, 2.0, 3.0,
        4.0, 5.0, 6.0, 7.0,
        8.0, 9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    }};

    mat_4x4 decending = {.elements = {
        15.0, 14.0, 13.0, 12.0, 
        11.0, 10.0,  9.0,  8.0, 
         7.0,  6.0,  5.0,  4.0,
         3.0,  2.0,  1.0,  0.0
    }};

    
    mat_4x4 result = mat_4x4_add(accending, decending); 


    TESTISTRUE(mat_4x4_equal(control, result));
}



bool test_mat_4x4_negate() { 
    mat_4x4 control = {.elements = {
         -0.0,  -1.0,  -2.0,  -3.0,
         -4.0,  -5.0,  -6.0,  -7.0, 
         -8.0,  -9.0, -10.0,  -11.0,
        -12.0, -13.0, -14.0, -15.0 
    }};

    mat_4x4 matrix = {.elements = {
          0.0,  1.0,  2.0,  3.0,
          4.0,  5.0,  6.0,  7.0,
          8.0,  9.0, 10.0, 11.0,
         12.0, 13.0, 14.0, 15.0
    }};

    mat_4x4 negate = mat_4x4_negate(matrix);

    TESTISTRUE( mat_4x4_equal(control, negate));
}
bool test_mat_4x4_sub() {
    mat_4x4 control = {.elements = { 
        15.0, 15.0, 15.0, 15.0,
        15.0, 15.0, 15.0, 15.0,
        15.0, 15.0, 15.0, 15.0,
        15.0, 15.0, 15.0, 15.0
    }};

    mat_4x4 lhs = {.elements = {
        60.0, 60.0, 60.0, 60.0,
        60.0, 60.0, 60.0, 60.0,
        60.0, 60.0, 60.0, 60.0,
        60.0, 60.0, 60.0, 60.0
    }};

    mat_4x4 rhs = {.elements = {
        45.0, 45.0, 45.0, 45.0,
        45.0, 45.0, 45.0, 45.0,
        45.0, 45.0, 45.0, 45.0,
        45.0, 45.0, 45.0, 45.0
    }};

    mat_4x4 difference = mat_4x4_sub(lhs, rhs);

    TESTISTRUE( mat_4x4_equal(control, difference));
}

bool test_mat_4x4_mult() {
    mat_4x4 control1 = {.elements = {
         34.0,  28.0,  22.0,  16.0,
        178.0, 156.0, 134.0, 112.0,
        322.0, 284.0, 246.0, 208.0,
        466.0, 412.0, 358.0, 304.0
    }};

    mat_4x4 control2 = {.elements = {
        304.0, 358.0, 412.0, 466.0,
        208.0, 246.0, 284.0, 322.0,
        112.0, 134.0, 156.0, 178.0,
         16.0,  22.0,  28.0,  34.0
    }};

    mat_4x4 mat1 = {.elements = {
        0.0,   1.0,  2.0,  3.0,
        4.0,   5.0,  6.0,  7.0,
        8.0,   9.0, 10.0, 11.0,
        12.0, 13.0, 14.0, 15.0
    }};

    mat_4x4 mat2 = {.elements = {
        15.0, 14.0, 13.0, 12.0, 
        11.0, 10.0,  9.0,  8.0, 
         7.0,  6.0,  5.0,  4.0,
         3.0,  2.0,  1.0,  0.0
    }};

    bool correct = true;

    mat_4x4 product1 = mat_4x4_mult(mat1, mat2);
    mat_4x4 product2 = mat_4x4_mult(mat2, mat1);
    correct &= mat_4x4_equal(control1, product1);
    correct &= mat_4x4_equal(control2, product2);
    TESTISTRUE(correct);
}

void test_mat_3x3() {

    test_mat_3x3_equal();
    test_mat_3x3_new();
    test_mat_3x3_predefined_matrices();
    test_mat_3x3_get();
    test_mat_3x3_get_row();
    test_mat_3x3_get_col();
    test_mat_3x3_set();
    test_mat_3x3_add();
    test_mat_3x3_negate();
    test_mat_3x3_sub();
    test_mat_3x3_mult();
}

void test_mat_4x4() {
    test_mat_4x4_equal();
    test_mat_4x4_new();
    test_mat_4x4_predefined_matrices();
    test_mat_4x4_get();
    test_mat_4x4_get_row();
    test_mat_4x4_get_col();
    test_mat_4x4_set();
    test_mat_4x4_add();
    test_mat_4x4_negate();
    test_mat_4x4_sub();
    test_mat_4x4_mult();
}

int main(int argc, char* argv[]) {
    test_mat_3x3();
    test_mat_4x4();
    return 0;
}


#undef RESET
#undef GREEN
#undef RED