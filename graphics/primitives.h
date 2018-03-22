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
	Vec4D colour;
	struct Texture* tex;
};

struct Primitive prim_new(enum PrimitiveType type, float* vertices, Vec4D colour);







struct Line {
	uint32 vbo, vao;
	struct Shader* shader;
	Vec4D colour;
};

struct Triangle {
	uint32 vbo, vao;
	struct Shader* shader;
	Vec4D colour;
};

struct Quad {
	uint32 vbo, vao;
	struct Shader* shader;
	Vec4D colour;
};

struct Cube {
	uint32 vbo, vao;
	struct Shader* shader;
	Vec4D colour;
};

struct Frustum {
	float near, far, fov;
	uint16 width, height;
};

struct Line line_new(Vec3D start, Vec3D end, Vec4D colour, struct Shader* shader);
void line_draw(struct Line* line);

struct Triangle triangle_new(float* vertices, Vec4D colour, struct Shader* shader);
void triangle_draw(struct Triangle* tri);

struct Quad quad_new(float* vertices, Vec4D colour, struct Shader* shader);
void quad_draw(struct Quad* quad);

// struct Cube cube_new(float* vertices);

#endif
