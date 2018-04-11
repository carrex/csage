#ifndef TEXTURE_H
#define TEXTURE_H

#include <lib/SDL/SDL.h>

struct Texture {
    uint32 id;
    uint16 w, h;
    uint8* data;
};

struct Texture* texture_new(char const* fname);

#endif
