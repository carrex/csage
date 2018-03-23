#ifndef SHADER_H
#define SHADER_H

#define SHADER_BUFFER_SIZE 512

struct Shader {
    uint32 vshader, fshader;
    uint32 program;
};

char slog[SHADER_BUFFER_SIZE];

struct Shader shader_new(char* vssrc, char* fssrc);
uint32 shader_new_vshader(const char* src);
uint32 shader_new_fshader(const char* src);
int32 shader_get_uniform(struct Shader* shader, char* name);
void shader_set_vec4(struct Shader* shader, char* name, float* vec);
void shader_set_mat4(struct Shader* shader, char* name, float* mat);

#endif
