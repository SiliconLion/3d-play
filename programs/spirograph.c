#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    // #include <OpenGL/gl3ext.h>
    #include <GLFW/glfw3.h>
#endif

#include <stdbool.h>
#include <time.h>

#include "geometry.h"
#include "shader.h"
#include "primatives.h"
#include "framebuffer.h"
#include "fourier.h"
#include "texture.h"


//updates the glViewport when the window is resized.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    printf("NEED TO UPDATE THE FRAMEBUFFER");
} 


int main(int argc, char *argv[]) {

    srand(time(NULL));

//    const char * fragmentfile;
//
//    if (argc > 1) {
//        fragmentfile = argv[1];
//        //important to check the user input. printf is vunerable
//        if (
//            strcmp(fragmentfile, "spirograph.frag") ==0
//            ) {
//                //things are good. do nothing.
//        } else {
//            printf("input is not a valid shader;");
//            return -1;
//        }
//    } else {
//        fragmentfile = "stylus.frag";
//    }
//
//    printf("%s", fragmentfile);
//
////just putting together the location of the fragment shader file.
//    char * fragFileLoc = calloc(500, sizeof(char));
//    strcat(fragFileLoc, "shaders/spirograph/");
//    strcat(fragFileLoc, fragmentfile);
//
//    printf("%s\n", fragFileLoc);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //needed for mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "3D Play :D", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwMakeContextCurrent(window);

    // During init, enable debug output
//    glEnable              ( GL_DEBUG_OUTPUT);
//    glDebugMessageCallback( MessageCallback, 0 );

    //adds the callback we defined above to a change in framebuffer size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    Framebuffer stylus_history;
    framebuffer_new(&stylus_history, GL_RGBA, 800, 600);
//    Geometry * surface = prim_new_plane(2, 2, 1, 1, GL_STATIC_DRAW);
//    FullGeometry surface = prim_new_text_rect(GL_STATIC_DRAW);
//    Shader *stylus_shad = shad_new("shaders/spirograph/stylus.vert", "shaders/spirograph/stylus.frag");
    FullGeometry surface = prim_new_tex_rect(GL_STATIC_DRAW);
    Shader *screen_shad = shad_new("shaders/spirograph/screen.vert", "shaders/spirograph/screen.frag");


//    int time_loc = glGetUniformLocation(stylus_shad->program, "aTime");
//    int dim_loc = glGetUniformLocation(stylus_shad->program, "aDimensions");
//    // int zoom_loc = glGetUniformLocation(shad->program, "aZoom");
//    int stylus_loc = glGetUniformLocation(stylus_shad->program, "aStylus");

//    int tex_loc = glGetUniformLocation(screen_shad->program, "screenTexture");


    GLERROR();

//    Texture * tex = tex_new("assets/matcap/check_reflection.png", true);


    //Clears the window
    glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    shad_bind(screen_shad);
//    tex_bind(tex, 0);

    full_geom_draw(&surface);

    //Present to viewport
    glfwSwapBuffers(window);

    while(!glfwWindowShouldClose(window)) {
//End of frame updates
        glfwPollEvents();
    }

}


    // Wanderer balls[30];
    // for(int i = 0; i < 30; i++) {
    //     wander_init(balls + i);
    // }

//    Wanderer stylus;
//    wander_init(&stylus);
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
////Clears the window
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
//
//
////draws the texture 1 time
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    framebuffer_bind(&stylus_history);
//    //skipping the uniforms not using here
//    shad_bind(stylus_shad);
//    full_geom_draw(&surface);
//
////Saves the texture we drew to an image
//    framebuffer_save_image(&stylus_history, "result.png");
//
////back to window drawing;
//    framebuffer_unbind();
//
//    GLERROR();
//
//
//    float counter = 0.0;
//    while(!glfwWindowShouldClose(window)) {
//        GLint viewportDimensions[4];
//        glGetIntegerv( GL_VIEWPORT, viewportDimensions );
//
////make sure everything is unbound and defaults are cleared.
//        framebuffer_unbind();
//        glClearColor(0.0, 0.0, 1.0, 1.0);
//        glClear(GL_COLOR_BUFFER_BIT);
//
////Draw the stylus to framebuffer
////        framebuffer_bind(&stylus_history);
////        shad_bind(stylus_shad);
////        //normally would call glClearColor, but we are intentionally not doing that, so the
////        //history of drawing on the texture is perserved.
////
////        glUniform1f(time_loc, counter);
////        glUniform2f(dim_loc, viewportDimensions[2], viewportDimensions[3]);
//////        glUniform3f(stylus_loc, stylus.m.x, stylus.m.y, stylus.m.radius);
////        glUniform3f(stylus_loc, 0.0, 0.0, 1.0);
////
////        geom_draw(surface);
////        framebuffer_unbind();
//
////Draw the framebuffer texture to the screen
//        //(default framebuffer is bound)
//
//        //clear the screen
//        glClearColor(0.0, 0.0, 1.0, 1.0);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        shad_bind(screen_shad);
//        glBindTexture(GL_TEXTURE_2D, stylus_history.tex_id);
//        glActiveTexture(GL_TEXTURE0);
//        full_geom_draw(&surface);
//
//
//
////Present to viewport
//        glfwSwapBuffers(window);
//
////End of frame updates
//        glfwPollEvents();
//
//        counter += 0.0001;
//        wanderer_update(&stylus, counter);
//    }
//
//    //arguably unnecessary
//    framebuffer_delete(&stylus_history);
//    full_geom_delete(&surface);
//    shad_delete(stylus_shad);
//
//
//    glfwTerminate();
//    return 0;
//
//}
//
//
//
