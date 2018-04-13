#include <SDL2/SDL.h>

#include "common.h"
#include "SOIL2.h"
#include "resourcemanager.h"
#include "texture.h"

struct Texture* texture_new(char const* fname)
{
    struct Texture* tex = smalloc(sizeof(struct Texture));
    glGenTextures(1, &tex->id);
    glBindTexture(GL_TEXTURE_2D, tex->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    tex->data = SOIL_load_image(fname, (int*)&tex->w, (int*)&tex->h, 0, SOIL_LOAD_AUTO);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->w, tex->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->data);
    glGenerateMipmap(GL_TEXTURE_2D);

    DEBUG("[GFX] Texture \"%s\" created", fname);
    DEBUG_GL();
    return tex;
}
