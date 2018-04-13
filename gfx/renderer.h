#ifndef RENDERER_H
#define RENDERER_H

#define RENDERER_MAX_PRIMITIVES 16
#define RENDERER_MAX_SPRITES 16

struct Renderer {
	struct Camera* camera;
	
	struct Primitive* prims[RENDERER_MAX_PRIMITIVES];
	struct Sprite* sprites[RENDERER_MAX_SPRITES];

	struct Shader* primshader;
	struct Shader* spriteshader;
};

struct Renderer renderer_new(struct Camera* cam);
void renderer_add_prim(struct Renderer* ren, struct Primitive* prim);
void renderer_add_sprite(struct Renderer* ren, struct Sprite* sprite);
void renderer_draw(struct Renderer* ren);

#endif
