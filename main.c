#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "common.h"
#include "maths/maths.h"
#include "graphics/graphics.h"
#include "resourcemanager.h"
#include "hashmap.h"
#include "config.h"

/* TODO
 *-->[RM] rm_load_png()?
 *-->[FN] flip image in rm_load_image(?)
 *-->[DB] Log file
 *-->[DB] DEBUG_SDL()
 */

int main(int argc, char** argv)
{
	(void)argc; (void)argv;
	DEBUG("\n\t=== === === %s === === ===", WINDOW_TITLE);
	if (load_config())
		DEBUG("[INIT] Configuration loaded");

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_X, WINDOW_Y, config.windoww, config.windowh, SDL_WINDOW_OPENGL);
	if (window)
		DEBUG("[INIT] SDL initialized");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glViewport(0, 0, 1280.0, 720.0);

	context = SDL_GL_CreateContext(window);
	if (context)
		DEBUG("[INIT] OpenGL context created: version %s", glGetString(GL_VERSION));
	SDL_GL_SetSwapInterval(0);

	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK)
		DEBUG("[INIT] GLEW initialized: version %s", glewGetString(GLEW_VERSION));
	glGetError(); // Glew bug creates an INVALID_ENUM on init

	if (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
		DEBUG("[INIT] SDL_image initialized");

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glLineWidth(3.0f);
	// glPolygoneMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);
	// glFrontFace(GL_CCW);

	DEBUG(" ");

	struct Camera   camera   = camera_new();
	struct Renderer renderer = renderer_new(&camera);

	struct Sprite s  = sprite_new((float[]){ 10, 10, 0 }, (float[]){ 32, 32, 0 }, "test.jpg");
	struct Sprite s2 = sprite_new((float[]){ 0.0, 0.0, 0 }, (float[]){ 0.5, 0.5, 0 }, "test.jpg");
	// struct Line line = line_new((Vec3D){-0.1f, -0.1f, 0.0f}, (Vec3D){-0.8f, -0.8f, 0.0f}, RED, NULL);
	// struct Triangle tri = triangle_new((float[]){0.75f, 0.25f, 0.0f, 0.5f, 0.5f, 0.0f, 0.25f, 0.25f, 0.0f}, BLUE, NULL);
	// struct Quad quad = quad_new((float[]){0.2f, 0.2f, 0.0f, 0.0f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f, -0.5f, 0.0f, 0.0f}, GREEN, NULL);
	struct Primitive xa = prim_new(PRIMITIVE_LINE, (float[]){ -720.0f, 0.0f, 0.0f, 720.0f, 0.0f, 0.0f }, RED);
	struct Primitive ya = prim_new(PRIMITIVE_LINE, (float[]){ 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, GREEN);
	struct Primitive za = prim_new(PRIMITIVE_LINE, (float[]){ 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f }, BLUE);
	// struct Texture tex = tex_new("tex.jpg");
	// float tpos[] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };
	// struct Primitive tri = prim_new(PRIMITIVE_TRIANGLE, (float[]){ 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -0.5f, 0.0f, 0.0f }, NULL,
	// 	                            &tex, tpos);
	// struct Primitive quad1 = prim_new(PRIMITIVE_QUAD, (float[]){0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.0f}, RED);
	// struct Primitive quad2 = prim_new(PRIMITIVE_QUAD, (float[]){0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f}, GREEN);
	// struct Primitive quad3 = prim_new(PRIMITIVE_QUAD, (float[]){0.0f, 0.0f, 0.0f, 0.0f, -0.3f, 0.0f, -0.3f, -0.3f, 0.0f, -0.3f, 0.0f, 0.0f}, BLUE);
	renderer_add_prim(&renderer, &xa);
	renderer_add_prim(&renderer, &ya);
	renderer_add_prim(&renderer, &za);
	// renderer_add_prim(&renderer, &tri);
	// renderer_add_prim(&renderer, &quad1);
	// renderer_add_prim(&renderer, &quad2);
	// renderer_add_prim(&renderer, &quad3);
	renderer_add_sprite(&renderer, &s);
	// renderer_add_sprite(&renderer, &s2);

	DEBUG("\n\tBeginning main loop\n"
	  "-----------------------------------");
	uint32 ntime, otime = 0;
	double dt, bank = 0;
	while (1) {
		ntime = SDL_GetTicks();
		dt    = (double)(ntime - otime);
		otime = ntime;
		bank += (uint32)dt;
		dt   *= 1e-3;
		while (bank >= LOGIC_FPS) {
			bank -= LOGIC_FPS;

			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					quit();
				} else if (event.type == SDL_KEYDOWN) {
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE: quit();
						case SDLK_a: camera_move_ortho(&camera, (float)dt, DIR_LEFT)    ; break;
						case SDLK_d: camera_move_ortho(&camera, (float)dt, DIR_RIGHT)   ; break;
						case SDLK_q: camera_move_ortho(&camera, (float)dt, DIR_UP)      ; break;
						case SDLK_e: camera_move_ortho(&camera, (float)dt, DIR_DOWN)    ; break;
						case SDLK_w: camera_move_ortho(&camera, (float)dt, DIR_FORWARD) ; break;
						case SDLK_s: camera_move_ortho(&camera, (float)dt, DIR_BACKWARD); break;
						case SDLK_LEFT : camera_rotate_ortho(&camera, (float)dt, DIR_LEFT) ; break;
						case SDLK_RIGHT: camera_rotate_ortho(&camera, (float)dt, DIR_RIGHT); break;
						case SDLK_UP   : camera_rotate_ortho(&camera, (float)dt, DIR_UP)   ; break;
						case SDLK_DOWN : camera_rotate_ortho(&camera, (float)dt, DIR_DOWN) ; break;
					}
				} else if (event.type == SDL_KEYUP) {

				}
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer_draw(&renderer);
		SDL_GL_SwapWindow(window);

		// quit();
	}

	return 0;
}

bool load_config()
{
	config = (struct Config){
		.windoww = 1280,
		.windowh = 720,
	};

	return true;
}

void quit()
{
	IMG_Quit();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	exit(0);
}
