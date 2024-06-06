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
//#include "texture.h"


//I know I know. Globals.
//ToDo: Do this in a non-global variable way
//these are set via `glfwGetFramebufferSize`
int WINDOW_WIDTH = 0;
int WINDOW_HEIGHT = 0;


//updates the glViewport when the window is resized.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("NEED TO UPDATE THE FRAMEBUFFER\n"); //TODO
}


int main(int argc, char *argv[]) {

    srand(time(NULL));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //needed for mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(600, 800, "3D Play :D", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    //there's a bunch of reasons why the actual framebuffer created might be a different size than
    //the numbers we pass to `glfwCreateWindow`. Including that screen coordinates and pixel counts
    //are not always the same. (like on my macbook pro).
    //TODO: Fix this on the rest of the demos
    glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwMakeContextCurrent(window);

    // During init, enable debug output
//    glEnable              ( GL_DEBUG_OUTPUT);
//    glDebugMessageCallback( MessageCallback, 0 );

    //adds the callback we defined above to a change in framebuffer size
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    Framebuffer stylus_history_1, stylus_history_2;
    framebuffer_new(&stylus_history_1, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT);
    framebuffer_new(&stylus_history_2, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT);

    Shader *stylus_shad = shad_new("shaders/random-walker/stylus.vert", "shaders/random-walker/stylus.frag");
    //This geometry is used in multiple ways/places as it's just a textured rect with convenient coords
    FullGeometry surface = prim_new_tex_rect(GL_STATIC_DRAW);
    Shader *screen_shad = shad_new("shaders/random-walker/screen.vert", "shaders/random-walker/screen.frag");


//    Texture * tex = tex_new("assets/matcap/check_reflection.png", true);


    int screenDimsLoc = glGetUniformLocation(screen_shad->program, "screenDims");
    int stylusPosLoc = glGetUniformLocation(stylus_shad->program, "stylusPos");
    int stylusHistoryLoc = glGetUniformLocation(stylus_shad->program, "stylusHistory");
    int frameColorLoc = glGetUniformLocation(stylus_shad->program, "framecolor");

    GLERROR();


    //Clears the screen
    glClearColor(0.3f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


//Main Loop
    float wander_speed = 0.01f; //max movement in a frame
    float color_shift_speed = 0.01f;

    long frame = 0;

    Framebuffer* activeBuff = &stylus_history_1;
    Framebuffer* prevFrameActiveBuff = &stylus_history_2;

    struct {float x, y;} stylus = {0.f, 0.f};
    struct {float r,g,b;} color = {0.5f, 0.5f, 0.5f};

    while(!glfwWindowShouldClose(window)) {

        //"game logic"
        stylus.x += (norm_rand() - 0.5f) * wander_speed * 2;
        stylus.y += (norm_rand() - 0.5f) * wander_speed * 2;

        color.r += (norm_rand() - 0.5f) * color_shift_speed * 2;
        color.g += (norm_rand() - 0.5f) * color_shift_speed * 2;
        color.b += (norm_rand() - 0.5f) * color_shift_speed * 2;

        //trying to keep them close to the screen without a border artifact being drawn
        if(stylus.x > 1.3) { stylus.x = 1.25; }
        if(stylus.y > 1.3) { stylus.y = 1.25; }
        if(stylus.x < -1.3) { stylus.x = -1.25; }
        if(stylus.y < -1.3) { stylus.y = -1.25; }

        if(color.r > 1.0) { color.r = 0.99; }
        if(color.g > 1.0) { color.g = 0.99; }
        if(color.b > 1.0) { color.b = 0.99; }

        if(color.r < 0.0) { color.r = 0.01; }
        if(color.g < 0.0) { color.g = 0.01; }
        if(color.b < 0.0) { color.b = 0.01; }


        bool saveFrame = false;

        int state = glfwGetKey(window, GLFW_KEY_SPACE);
        if (state == GLFW_PRESS)
        {
           saveFrame = true;
        }


        //swaps the framebuffers (could also be done at end of frame)
        Framebuffer * temp = prevFrameActiveBuff;
        prevFrameActiveBuff = activeBuff;
        activeBuff = temp;


        //Binds the stylus stuff
        framebuffer_bind(activeBuff);
        shad_bind(stylus_shad);



        //Sets the Stylus Uniforms
        glBindTexture(GL_TEXTURE_2D, prevFrameActiveBuff->tex_id);
        glUniform2f(stylusPosLoc, stylus.x, stylus.y);
        glUniform3f(frameColorLoc, color.r, color.g, color.b);

        //Draws to the stylus framebuffer
        full_geom_draw(&surface);

        //Saves framebuffer to image
        if(saveFrame) {
            framebuffer_save_image(activeBuff, "walk.png");
        }

        //Binds Screen
        framebuffer_unbind();
        shad_bind(screen_shad);
        glBindTexture(GL_TEXTURE_2D, activeBuff->tex_id);
//    glBindTexture(GL_TEXTURE_2D, tex->id);

        //Clears the screen
        glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        //Set Screen Uniforms
        glUniform2f(screenDimsLoc, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);

        //Draw Screen
        full_geom_draw(&surface);

        //Present to viewport
        glfwSwapBuffers(window);


//End of frame updates
        frame += 1;
        glfwPollEvents();
    }

}
