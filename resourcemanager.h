#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL2/SDL.h>

#define GFX_PATH    "gfx/%s"
#define SHADER_PATH "shaders/%s"
#define MAX_SHADERS 8

#define rm_malloc(b)           _rm_malloc(b, __FILE__, __LINE__)
#define rm_calloc(i, b)        _rm_calloc(i, b, __FILE__, __LINE__)
#define rm_malloc_floats(i, d) _rm_malloc_floats(i, d, __FILE__, __LINE__)

char* rm_load_file(char* path);
char* rm_load_file_shader(char* fname);
SDL_Surface* rm_load_image(char* fname);
struct Shader* rm_new_shader(char* vssrc, char* fssrc);
void*  _rm_malloc(size_t bytes, char* file, uint16 line);
void*  _rm_calloc(size_t items, size_t bytes, char* file, uint16 line);
float* _rm_malloc_floats(size_t items, float* data, char* file, uint16 line);
uint32 fsize(FILE* file);

#endif
