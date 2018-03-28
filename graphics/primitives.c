#include "GL/glew.h"

#include "common.h"
#include "maths/maths.h"
#include "shader.h"
#include "texture.h"
#include "resourcemanager.h"
#include "primitives.h"

struct Primitive prim_new(enum PrimitiveType type, float* vertices, float* colour)
{
    struct Primitive prim = {
        .vcount   = type,
        .vertices = rm_malloc_floats(3*type, vertices),
    };
    vec_copy_4d(prim.colour, colour);

    glGenVertexArrays(1, &prim.vao);
    glBindVertexArray(prim.vao);

    uint32 vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(3*type*sizeof(float)), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, type, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    switch (type) {
        case PRIMITIVE_LINE    : prim.mode = GL_LINES       ; break;
        case PRIMITIVE_TRIANGLE: prim.mode = GL_TRIANGLES   ; break;
        case PRIMITIVE_QUAD    : prim.mode = GL_TRIANGLE_FAN; break;
        default: prim.mode = GL_POINTS;
    }

    return prim;
}
