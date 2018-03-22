#include <stdio.h>
#include <stdbool.h>

#include <GL/glew.h>

#include "common.h"
#include "maths/maths.h"
#include "renderer.h"
#include "resourcemanager.h"
#include "shader.h"

struct Shader shader_new(char* vssrc, char* fssrc)
{
    struct Shader shader;
    shader.vshader = shader_new_vshader(rm_load_file_shader(vssrc));
    shader.fshader = shader_new_fshader(rm_load_file_shader(fssrc));
    shader.program = glCreateProgram();
    glAttachShader(shader.program, shader.vshader);
    glAttachShader(shader.program, shader.fshader);
    glLinkProgram(shader.program);

    DEBUG("[GFX] Shader program created");
    DEBUG_GL();
    return shader;
}

uint32 shader_new_vshader(const char* src)
{
    uint32 shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int32 sstatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &sstatus);
    glGetShaderInfoLog(shader, SHADER_BUFFER_SIZE, NULL, slog);
    if (sstatus == GL_TRUE) {
        DEBUG("[GFX] Vertex shader compiled");
        DEBUG(slog);
    } else {
        ERROR("[GFX] Vertex shader failed to compile%s", slog);
        DEBUG("%s\n", src);
    }

    DEBUG_GL();
    return shader;
}

uint32 shader_new_fshader(const char* src)
{
    uint32 shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int32 sstatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &sstatus);
    glGetShaderInfoLog(shader, SHADER_BUFFER_SIZE, NULL, slog);
    if (sstatus == GL_TRUE) {
        DEBUG("[GFX] Fragment shader compiled");
        DEBUG(slog);
    } else {
        ERROR("[GFX] Fragment shader failed to compile%s", slog);
        DEBUG("%s", src);
    }

    DEBUG_GL();
    return shader;
}

/* TODO: Buffering for the location? */
int32 shader_get_uniform(struct Shader* shader, char* name)
{
    return glGetUniformLocation(shader->program, name);
}

void shader_set_vec4(struct Shader* shader, char* name, float* vec)
{
    int32 loc = shader_get_uniform(shader, name);
    ASSERT(!(loc < 0), false, "[GFX] Shader uniform \"%s\" not active", name);
    glUseProgram(shader->program);
    glUniform4fv(loc, 1, vec);
}

void _shader_set_mat4(struct Shader* shader, char* name, float* mat)
{
    int32 loc = shader_get_uniform(shader, name);
    ASSERT(!(loc < 0), false, "[GFX] Shader uniform \"%s\" not active", name);
    glUseProgram(shader->program);
    glUniformMatrix4fv(loc, 1, GL_TRUE, mat);
}
