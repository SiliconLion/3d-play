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

// bool test_mat_3x3_new_zero() {
//     mat_3x3 control = {.elements = {
//         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
//     }};
//     mat_3x3 zero = mat_3x3_new_zero();
//     TESTISTRUE(mat_3x3_equal(control, zero));
// }

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


void test_matrix() {

    test_mat_3x3_equal();
    test_mat_3x3_new();
    test_mat_3x3_predefined_matrices();
    test_mat_3x3_get();
    test_mat_3x3_get_row();
    test_mat_3x3_get_col();
    test_mat_3x3_set();
    test_mat_3x3_add();
    test_mat_3x3_mult();
}

int main(int argc, char* argv[]) {
    test_matrix();
    return 0;
}


#undef RESET
#undef GREEN
#undef RED