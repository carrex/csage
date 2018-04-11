#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <lib/SDL/SDL.h>

#include "common.h"
#include "maths/maths.h"
#include "util/file.h"
#include "graphics/graphics.h"
#include "resourcemanager.h"

struct Shader* rmshaders[MAX_SHADERS] = { 0 };
struct Texture* rmtextures[MAX_TEXTURES] = { 0 };
char rmpbuf[64];
size_t rmallocated = 0;

char* rm_load_file(char* path)
{
	/* TODO: rewrite with fread, etc. */
	FILE* file = fopen(path, "r");
	if (!file)
		ERROR("[RES] Failed to open file: %s", path);

	char* data = smalloc(file_size(file) + 1);
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

struct Shader* rm_new_shader(char* vssrc, char* fssrc)
{
	uint8 i = 0;
	while (rmshaders[i]) i++;
	if (i >= MAX_SHADERS)
		ERROR("[RES] Max shader count already reached");
	rmshaders[i]  = smalloc(sizeof(struct Shader));
	*rmshaders[i] = shader_new(vssrc, fssrc);

	DEBUG("[RES] New shader created");
	return rmshaders[i];
}

