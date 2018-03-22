#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "common.h"
#include "resourcemanager.h"
#include "texture.h"

struct Texture tex_new(char* fname)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    struct Texture tex;
    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);

    tex.img = rm_load_image(fname);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.img->w, tex.img->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex.img->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    DEBUG("[GFX] Texture created successfully");
    DEBUG_GL();
    return tex;
}
