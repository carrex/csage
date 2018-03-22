#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

struct Texture {
    uint32 id;
    SDL_Surface* img;
};

struct Texture tex_new(char* fname);

#endif
