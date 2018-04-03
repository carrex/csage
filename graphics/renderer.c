#include <GL/glew.h>

#include "common.h"
#include "maths/maths.h"
#include "resourcemanager.h"
#include "graphics.h"
#include "camera.h"
#include "renderer.h"

struct Renderer renderer_new(struct Camera* cam)
{
	struct Renderer ren = {
		.camera       = cam,
		.prims        = { 0 },
		.sprites      = { 0 },
		.primshader   = rm_new_shader("primitive.vert", "primitive.frag"),
		.spriteshader = rm_new_shader("sprite.vert", "sprite.frag"),
	};

	return ren;
}

void renderer_add_prim(struct Renderer* ren, struct Primitive* prim)
{
	uint16 i = 0;
	while (ren->prims[i]) i++;
	ren->prims[i] = prim;
}

void renderer_add_sprite(struct Renderer* ren, struct Sprite* sprite)
{
	uint16 i = 0;
	while (ren->sprites[i]) i++;
	ren->sprites[i] = sprite;
}

void renderer_draw(struct Renderer* ren)
{
	glUseProgram(ren->primshader->program);
	shader_set_mat4(ren->primshader, "view", ren->camera->view);
	shader_set_mat4(ren->primshader, "proj", ren->camera->proj);
	for (uint8 i = 0; ren->prims[i]; i++) {
		shader_set_mat4(ren->primshader, "model" , I4A);
		shader_set_vec4(ren->primshader, "colour", ren->prims[i]->colour);

		glBindVertexArray(ren->prims[i]->vao);
		glDrawArrays(ren->prims[i]->mode, 0, ren->prims[i]->vcount);
	}

	glUseProgram(ren->spriteshader->program);
	shader_set_mat4(ren->spriteshader, "view" , ren->camera->view);
	shader_set_mat4(ren->spriteshader, "proj" , ren->camera->proj);
	for (uint8 i = 0; ren->sprites[i]; i++) {
		shader_set_mat4(ren->spriteshader, "model", ren->sprites[i]->model);

		glBindVertexArray(ren->sprites[i]->vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
	}
}
