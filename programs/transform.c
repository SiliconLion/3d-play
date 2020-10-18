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
#include "texture.h"
#include "transformation.h"


void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

//updates the glViewport when the window is resized.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

int main() {

    if(!glfwInit()) {
        return 2; 
    }

    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //needed for mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow * window = glfwCreateWindow(640, 480, "Transform", NULL, NULL);
    if(!window) {
        return 2;
    }

    glfwMakeContextCurrent(window);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //to avoid screen tearing. 
    glfwSwapInterval(1);



    Geometry * geom = geom_from_stl("assets/models/mushu.stl");

    Shader * shad = shad_new("shaders/transform/vertex.vert", "shaders/transform/fragment.frag");

    Texture * texture = tex_new("assets/matcap/clay_brown.png", true);


    unsigned int transform_loc = glGetUniformLocation(shad->program, "transformation");


    float counter = 0.0;

    shad_bind(shad);
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


        tran_chain chain = tran_chain_new();
        tran_chain_add(&chain, trans_new_x_rot(counter));
        tran_chain_add(&chain, trans_new_y_rot(counter));
        tran_chain_add(&chain, trans_new_z_rot(counter));

        transform trans = tran_chain_squash(&chain);

        glUniformMatrix4fv(
                transform_loc,
                1,
                GL_FALSE,
                &(trans.elements)
        );
       
        tex_bind(texture, 0);

        geom_draw(geom);

        glfwSwapBuffers(window);
        
        glfwPollEvents();

        counter += 0.05;
    }      


    glfwDestroyWindow(window);
    glfwTerminate();
}