#include "GL/glew.h"

#include "common.h"
#include "maths/maths.h"
#include "resourcemanager.h"
#include "sprite.h"

struct Sprite sprite_new(float* pos, float* size, char* tex)
{
	struct Sprite sprite;
    matrix_copy(sprite.model, I4, 4);
    sprite_move(&sprite, pos);
    sprite_resize(&sprite, size);
    matrix_print(sprite.model, 4);

    float vertices[] = {  1.0f,  1.0f, 0.0f, 1.0f, 0.0f,    // top right
                         -1.0f,  1.0f, 0.0f, 0.0f, 0.0f,    // top left
                         -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,    // bottom left
                          1.0f, -1.0f, 0.0f, 1.0f, 1.0f, }; // bottom right
    uint8 indices[] = { 3, 0, 1,
                        3, 1, 2, };
    uint32 vbo, ebo;
    glGenVertexArrays(1, &sprite.vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(sprite.vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));

    sprite.texture = rm_new_texture(tex);

    DEBUG("[GFX] Created new sprite (%s)", tex);
    DEBUG_GL();
    return sprite;
}

void sprite_move(struct Sprite* sprite, float* vec)
{
    matrix_translate_add(sprite->model, vec);
}

void sprite_move_to(struct Sprite* sprite, float* pos)
{
    matrix_translate(sprite->model, pos);
}

void sprite_resize(struct Sprite* sprite, float* size)
{
    matrix_scale(sprite->model, size);
}
