#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GL/glew.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "common.h"
#include "maths/maths.h"
#include "graphics/graphics.h"
#include "resourcemanager.h"

/* TODO
 * * rm_load_shader()
 * * prevent loading assets more than once (hashmap)
 */

struct Shader* rmshaders[MAX_SHADERS] = {0};
char rmpbuf[64];
size_t rmallocated = 0;

char* rm_load_file(char* path)
{
    FILE* file = fopen(path, "r");
    if (!file)
        ERROR("[RES] Failed to open file: %s", path);

    char* data = rm_malloc(fsize(file) + 1);
    int i = 0;
    for (int c; (c = fgetc(file)) != EOF; i++)
        data[i] = (char)c;
    data[i] = '\0';

    DEBUG("[RES] File loaded: %s", path);
    fclose(file);
    return data;
}

char* rm_load_file_shader(char* fname)
{
    sprintf(rmpbuf, SHADER_PATH, fname);

    return rm_load_file(rmpbuf);
}

SDL_Surface* rm_load_image(char* fname)
{
    sprintf(rmpbuf, GFX_PATH, fname);
	SDL_Surface* img = IMG_Load(rmpbuf);
    if (!img)
        ERROR("[RES] Failed to load image: %s", IMG_GetError());
    else
        DEBUG("[RES] Image loaded: %s", rmpbuf);
    /* Not sure how good this is */
    SDL_SetSurfaceRLE(img, 1);
    SDL_LockSurface(img);

    return img;
}

struct Shader* rm_new_shader(char* vssrc, char* fssrc)
{
    uint8 i = 0;
    while (rmshaders[i]) i++;
    ASSERT(i <= MAX_SHADERS, false, "[RES] Max shader count already reached");
    rmshaders[i]  = rm_malloc(sizeof(struct Shader));
    *rmshaders[i] = shader_new(vssrc, fssrc);

    DEBUG("[RES] New shader created");
    return rmshaders[i];
}

void* _rm_malloc(size_t bytes, char* file, uint16 line)
{
    void* mem = malloc(bytes);
    if (!mem) {
        ERROR("[RES] Memory allocation failed");
        return NULL;
    } else {
        rmallocated += bytes;
        DEBUG("[RES] Memory allocated (%s:%u): %u bytes (%.2f kB) (%.2f kB total)",
              file, line, (uint32)bytes, bytes/1024.0, rmallocated/1024.0);
    }

    return mem;
}

void* _rm_calloc(size_t items, size_t bytes, char* file, uint16 line)
{
    void* mem = calloc(items, bytes);
    if (!mem) {
        ERROR("[RES] Memory allocation failed");
        return NULL;
    } else {
        rmallocated += bytes;
        DEBUG("[RES] Memory allocated (%s:%u): %u bytes (%.2f kB) (%.2f kB total)",
              file, line, (uint32)bytes, bytes/1024.0, rmallocated/1024.0);
    }

    return mem;
}

float* _rm_malloc_floats(size_t items, float* data, char* file, uint16 line)
{
    float* mem = malloc(items * sizeof(float));
    size_t bytes = items * sizeof(float);
    if (!mem) {
        ERROR("[RES] Memory allocation failed");
        return NULL;
    } else {
        rmallocated += bytes;
        DEBUG("[RES] Memory allocated (%s:%u): %u bytes (%.2f kB) (%.2f kB total)",
              file, line, (uint32)bytes, bytes/1024.0, rmallocated/1024.0);
    }
    for (size_t i = 0; i < items; i++)
        mem[i] = data[i];

    return mem;
}

uint32 fsize(FILE* file)
{
    fseek(file, 0, SEEK_END);
    uint32 size = (uint32)ftell(file) * sizeof(char);
    rewind(file);

    return size;
}
