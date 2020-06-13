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

//updates the glViewport when the window is resized.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

//nothing special, just processes input. its a function to keep things nice.
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char *argv[])
{
    
    const char*  model_path;
    if (argc == 2) {
        model_path = argv[1];
    } else {
        model_path = "assets/mushu.stl";
    }

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


    Geometry * geom = geom_from_stl(model_path);

    printf("geometry created\n");


    Shader * shad = shad_new("shaders/vertex.vert", "shaders/fragment.frag");

    printf("shader created\n");

    printf("verticies count: %i\n", geom->verticies_count);

    unsigned int angleY_loc = glGetUniformLocation(shad->program, "angleY");
    
    float angle = 0;
    shad_bind(shad);
    while(!glfwWindowShouldClose(window)) {

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        angle += 0.01;
        glUniform1f(angleY_loc, angle);

        geom_draw(geom);

        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;


}



