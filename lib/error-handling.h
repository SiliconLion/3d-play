#pragma once
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    #include <GLFW/glfw3.h>
#endif

void print_gl_error(int line, char* file) {
    int err = glGetError();
    if(err != 0) {
        printf("GL Error: %s:line %i : %i\n", line, file, err);
    }
}

#define GLERROR() \
        do{       \
            print_gl_error(__LINE__, __FILE__); \
        }while(0)
