#ifndef RENDERER_H
#define RENDERER_H

#define RENDERER_MAX_PRIMITIVES 8

struct Renderer {
	struct Camera* cam;
	
	struct Primitive* prims[RENDERER_MAX_PRIMITIVES];

	struct Shader* primshader;
};

struct Renderer ren_new(struct Camera* cam);
void ren_add_prim(struct Renderer* ren, struct Primitive* prim);
void ren_draw(struct Renderer* ren);

#endif
