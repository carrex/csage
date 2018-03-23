#include <GL/glew.h>

#include "common.h"
#include "maths/maths.h"
#include "resourcemanager.h"
#include "shader.h"
#include "texture.h"
#include "primitives.h"
#include "camera.h"
#include "renderer.h"

struct Renderer ren_new(struct Camera* cam)
{
	struct Renderer ren = {
		.cam = cam,
		.prims = { 0 },
		.primshader = rm_new_shader("primitive.vert", "primitive.frag"),
	};
	// for (uint16 i = 0; i < RENDERER_MAX_PRIMITIVES; i++)
	// 	ren.prims[i] = NULL;

	return ren;
}

void ren_add_prim(struct Renderer* ren, struct Primitive* prim)
{
	uint16 i = 0;
	while (ren->prims[i]) i++;
	ren->prims[i] = prim;
}

void ren_draw(struct Renderer* ren)
{
	// cam_calc_view(ren->cam);
	// cam_calc_proj(ren->cam);
	for (uint16 i = 0; ren->prims[i]; i++) {
		glUseProgram(ren->primshader->program);
		shader_set_vec4(ren->primshader, "colour", ren->prims[i]->colour);
		shader_set_mat4(ren->primshader, "model", (float[])I4);
		// shader_set_mat4(ren->primshader, "view", I4);
		// shader_set_mat4(ren->primshader, "proj", I4);
		shader_set_mat4(ren->primshader, "view", ren->cam->view);
		shader_set_mat4(ren->primshader, "proj", ren->cam->proj);
		glBindVertexArray(ren->prims[i]->vao);

		glDrawArrays(ren->prims[i]->mode, 0, ren->prims[i]->vcount);
	}
}
