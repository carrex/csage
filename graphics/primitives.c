#include "GL/glew.h"

#include "common.h"
#include "maths/maths.h"
#include "shader.h"
#include "texture.h"
#include "resourcemanager.h"
#include "primitives.h"

struct Primitive prim_new(enum PrimitiveType type, float* vertices, Vec4D colour)
{
    struct Primitive prim = {
        .vcount   = type,
        .vertices = rm_malloc_floats(type * 3, vertices),
    };
    vec_copy_4d(prim.colour, colour);

    glGenVertexArrays(1, &prim.vao);
    glBindVertexArray(prim.vao);

    uint32 vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, type*3*sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    switch (type) {
        case PRIMITIVE_LINE    : prim.mode = GL_LINES       ; break;
        case PRIMITIVE_TRIANGLE: prim.mode = GL_TRIANGLES   ; break;
        case PRIMITIVE_QUAD    : prim.mode = GL_TRIANGLE_FAN; break;
        default: prim.mode = GL_POINTS;
    }

    return prim;
}




struct Line line_new(Vec3D start, Vec3D end, Vec4D colour, struct Shader* shader)
{
    float vertices[] = { start[0], start[1], start[2],
                         end[0]  , end[1]  , end[2]  , };
    struct Line line;
    vec_copy_4d(line.colour, colour);
    if (!shader) {
        line.shader = rm_new_shader("primitive.vert", "primitive.frag");
        shader_set_mat4(line.shader, "model", I4);
        shader_set_mat4(line.shader, "view", I4);
        shader_set_mat4(line.shader, "proj", I4);
    } else {
        line.shader = shader;
    }

    glGenVertexArrays(1, &line.vao);
    glBindVertexArray(line.vao);

    glGenBuffers(1, &line.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, line.vbo);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    DEBUG("[RES] Line object created");
    DEBUG_GL();
    return line;
}

void line_draw(struct Line* line)
{
    glUseProgram(line->shader->program);
    shader_set_vec4(line->shader, "colour", line->colour);
    glBindVertexArray(line->vao);
    glDrawArrays(GL_LINES, 0, 2);
}

/*****************************************************************************/

struct Triangle triangle_new(float* vertices, Vec4D colour, struct Shader* shader)
{
    struct Triangle tri;
    vec_copy_4d(tri.colour, colour);
    if (!shader) {
        tri.shader = rm_new_shader("primitive.vert", "primitive.frag");
        shader_set_mat4(tri.shader, "model", I4);
        shader_set_mat4(tri.shader, "view", I4);
        shader_set_mat4(tri.shader, "proj", I4);
    } else {
        tri.shader = shader;
    }

    glGenVertexArrays(1, &tri.vao);
    glBindVertexArray(tri.vao);

    glGenBuffers(1, &tri.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, tri.vbo);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    DEBUG("[RES] Triangle object created");
    DEBUG_GL();
    return tri;
}

void triangle_draw(struct Triangle* tri)
{
	glUseProgram(tri->shader->program);
    shader_set_vec4(tri->shader, "colour", tri->colour);
	glBindVertexArray(tri->vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

/*****************************************************************************/

struct Quad quad_new(float* vertices, Vec4D colour, struct Shader* shader)
{
    struct Quad quad;
    vec_copy_4d(quad.colour, colour);
    if (!shader) {
        quad.shader = rm_new_shader("primitive.vert", "primitive.frag");
        shader_set_mat4(quad.shader, "model", I4);
        shader_set_mat4(quad.shader, "view", I4);
        shader_set_mat4(quad.shader, "proj", I4);
    } else {
        quad.shader = shader;
    }

    glGenVertexArrays(1, &quad.vao);
    glBindVertexArray(quad.vao);

    glGenBuffers(1, &quad.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, quad.vbo);
    glBufferData(GL_ARRAY_BUFFER, 12*sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    DEBUG("[RES] Quad object created");
    DEBUG_GL();
    return quad;
}

void quad_draw(struct Quad* quad)
{
	glUseProgram(quad->shader->program);
    shader_set_vec4(quad->shader, "colour", quad->colour);
	glBindVertexArray(quad->vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
