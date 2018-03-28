#ifndef TRIANGLE_H
#define TRIANGLE_H

enum PrimitiveType {
	PRIMITIVE_LINE     = 2,
	PRIMITIVE_TRIANGLE = 3,
	PRIMITIVE_QUAD     = 4,
};

struct Primitive {
	uint32 vao;
	float* vertices;
	uint8 vcount;

	uint32 mode;
	float colour[4];
};

struct Primitive prim_new(enum PrimitiveType type, float* vertices, float* colour);

#endif
