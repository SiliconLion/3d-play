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


int windowWidth_global, windowHeight_global;


void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

//updates the glViewport when the window is resized.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    windowWidth_global = width;
    windowHeight_global = height;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        int mode = glfwGetInputMode(window, GLFW_CURSOR);
        if (mode == GLFW_CURSOR_DISABLED) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

    } else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
        
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

    
    glfwGetFramebufferSize(window, &windowWidth_global, &windowHeight_global);
    glViewport(0, 0, windowWidth_global, windowHeight_global);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //to exit when escape is pressed.
    glfwSetKeyCallback(window, key_callback);
    
    //to avoid screen tearing. 
    glfwSwapInterval(1);

    //for better camera movement.
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Geometry * geom1 = geom_from_stl("assets/models/meshed_sphere.stl");
    Geometry * geom2 = geom_from_stl("assets/models/meshed_cube.stl");


    Shader * shad = shad_new("shaders/transform/vertex.vert", "shaders/transform/fragment.frag");

    Texture * texture = tex_new("assets/matcap/clay_brown.png", true);


    unsigned int transform_loc = glGetUniformLocation(shad->program, "transformation");

    shad_bind(shad);

    float xrot = 0;
    float yrot = 0;

    float  prev_xpos = 0;
    float  prev_ypos = 0; 
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


        double curr_xpos, curr_ypos;
        glfwGetCursorPos(window, &curr_xpos, &curr_ypos);

    //a movement along the x axis corisponds to a rotation around the y axis and visaversa. 
        yrot += -1.0f * (curr_xpos - prev_xpos) / (windowWidth_global / 2);
        xrot += -1.0f * (curr_ypos - prev_ypos) / (windowHeight_global / 2);

        prev_xpos = curr_xpos;
        prev_ypos = curr_ypos;

        // printf("xrot: %f, yrot: %f\n", xrot, yrot);

        tran_chain chain = tran_chain_new();
        tran_chain_add(&chain, trans_new_y_rot(yrot) );
        tran_chain_add(&chain, trans_new_x_rot(xrot) );
        tran_chain_add(&chain, trans_new_scale(0.5, 0.5, 0.5));
        transform trans = tran_chain_squash(&chain);
        trans_send_uniform(transform_loc, trans);
       

        tex_bind(texture, 0);

        geom_draw(geom1);
        geom_draw(geom2);

        glfwSwapBuffers(window);
        
        glfwPollEvents();


    }      


    glfwDestroyWindow(window);
    glfwTerminate();
}