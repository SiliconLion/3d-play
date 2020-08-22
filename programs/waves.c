#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    // #include <OpenGL/gl3ext.h>
    #include <GLFW/glfw3.h>
#endif

#include <stdbool.h>

#include "stlreader.h"
#include "geometry.h"
#include "shader.h"
#include "primatives.h"
// #include "texture.h"



//updates the glViewport when the window is resized.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 


int main(int argc, char *argv[]) {


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //needed for mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Play :D", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwMakeContextCurrent(window);

    //adds the callback we defined above to a change in framebuffer size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    Geometry * surface = prim_new_plane(2, 2, 1, 1, GL_STATIC_DRAW);


    Shader * shad = shad_new("shaders/waves/vertex.vert", "shaders/waves/fragment.frag");

    unsigned int time_loc = glGetUniformLocation(shad->program, "time");


    shad_bind(shad);

    float counter = 0.0;
    while(!glfwWindowShouldClose(window)) {
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    //makes it wireframe (for debug purposes)
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
        // glFrontFace(GL_CW);

        glUniform1f(time_loc, counter);

        geom_draw(surface);

        glfwSwapBuffers(window);
        
        glfwPollEvents();

        counter += 0.01;
    }

    glfwTerminate();
    return 0;
    
}



