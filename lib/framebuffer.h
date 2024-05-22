#pragma once
#ifdef __APPLE__
#include <OpenGL/gl3.h>
// #include <OpenGL/gl3ext.h>
#include <GLFW/glfw3.h>
#include <inttypes.h>

#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
#endif
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
    #define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

//#include "stb_image.h"
#include "stb_image_write.h"

#include "error-handling.h"

//TODO: Support renderbuffer attachments, not just texture attachments
//TODO: Support depth and stencil textures
//TODO: Support multitexture Frambuffers?
typedef struct {
    unsigned int fbo_id;
    unsigned int tex_id; //should probably modify this to be just a "Texture" object
    unsigned int width;
    unsigned int height;
    int32_t pixel_format;
} Framebuffer; //FBO for short. "frame buffer object"


//Note: Apparently there are some issues with many drivers when trying to reuse an FBO across
// things like a resize. So here, best practice is to delete and create a totally new FBO

void framebuffer_new(Framebuffer* f, int32_t pixel_format, int32_t width, int32_t height) {
    glGenFramebuffers(1, &f->fbo_id);
    glGenTextures(1, &f->tex_id);
    f->pixel_format = pixel_format;
    f->width = width;
    f->height = height;

    glBindFramebuffer(GL_FRAMEBUFFER, f->fbo_id);
    glBindTexture(GL_TEXTURE_2D, f->tex_id);



    glTexImage2D(
            GL_TEXTURE_2D, 0,
            pixel_format, width, height,0,
            pixel_format, GL_UNSIGNED_BYTE, NULL
            );

    //we dont really care about mipmaps or anything cuz it matches the viewport.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //A little unsure about the attachment variable, but i think it's "which component do we want to
    //bind to as level 0". So we might have an RGBA texture, but want to bind the green component as level 0.
    //For our purposes, we are gonna keep it much simpler than that and just bind the base color component
    //as the base color component.
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, f->tex_id, 0);

    uint32_t status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if( status != GL_FRAMEBUFFER_COMPLETE) {
        printf("Error creating Frame Buffer Object. Error: %" PRIu32 "\n", status);
    }
    uint32_t err = glGetError();
    if( err != GL_NO_ERROR) {
        printf("Error creating Frame Buffer Object. Error: %" PRIu32 "\n", err);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



void framebuffer_bind(Framebuffer* f) {
    glBindFramebuffer(GL_FRAMEBUFFER, f->fbo_id);
}

//void framebuffer_bind_read(Framebuffer* f) {
//    glBindFramebuffer(GL_READ_FRAMEBUFFER, f->fbo_id);
//}
//
//void framebuffer_bind_draw(Framebuffer* f) {
//    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, f->fbo_id);
//}

//usually technically does not need to be called, but prevents the wrong framebuffer being written to
void framebuffer_unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void framebuffer_delete(Framebuffer* f) {
    glDeleteTextures(1, &f->tex_id);
    glDeleteFramebuffers(1, &f->fbo_id);
}

void framebuffer_save_image(Framebuffer* f, const char* file_path) {
    unsigned char *data;
    data = calloc(f->width * f->height * 3, sizeof(unsigned char));
    if(!data) { printf("Out of memory."); exit(-1);}
    glBindTexture(GL_TEXTURE_2D, f->tex_id);

    //sets the pixel store mode
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    GLERROR();

    stbi_flip_vertically_on_write(true);
    int ret = stbi_write_png(file_path, f->width, f->height, 4, data, 4);
    if (ret == 0)
    {
        printf("Error: Cannot save image from framebuffer. (may be many possibilities but check filepath)\n");
    }

    free(data);
}


#endif