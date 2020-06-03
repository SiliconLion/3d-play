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

int main()
{

    // glfwInit();
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // //needed for mac
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    // if (window == NULL)
    // {
    //     printf("Failed to create GLFW window\n");
    //     glfwTerminate();
    //     return -1;
    // }
    // glfwMakeContextCurrent(window);
    // glViewport(0, 0, 800, 600);

    // //adds the callback we defined above to a change in framebuffer size
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // Geometry * geom = geom_from_stl("assets/fox.stl");

    // printf("geometry created\n");

    // Shader * shad = shad_new("shaders/vertex.vert", "shaders/fragment.frag");

    // printf("shader created\n");

    // shad_bind(shad);
    // while(!glfwWindowShouldClose(window)) {

    //     processInput(window);

    //     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //     glClear(GL_COLOR_BUFFER_BIT);

    //     geom_draw(geom);

    //     glfwSwapBuffers(window);
        
    //     glfwPollEvents();
    // }

    // glfwTerminate();
    // return 0;

    stl_obj * obj = stl_from_file("assets/Mushu.stl");
    stl_normalize(obj, 1.0);
    stl_to_file(obj, "output/Mushu.stl");
}



