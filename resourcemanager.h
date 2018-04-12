#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL2/SDL.h>

#define GFX_PATH    "assets/gfx/%s"
#define SHADER_PATH "shaders/%s"
#define MAX_SHADERS  8
#define MAX_TEXTURES 8

char* rm_load_file(char* path);
char* rm_load_file_shader(char* fname);
struct Shader* rm_new_shader(char* vssrc, char* fssrc);
struct Texture* rm_new_texture(char* fname);

#endif
