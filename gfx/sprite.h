#ifndef SPRITE_H
#define SPRITE_H

struct Sprite {
	float model[16];

	uint32 vao;
	struct Texture* tex;
};

struct Sprite sprite_new(float* pos, float* size, char* texture);
void sprite_move(struct Sprite* sprite, float* vec);
void sprite_resize(struct Sprite* sprite, float* size);

#endif
