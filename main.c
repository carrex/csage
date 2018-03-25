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
#include "main.h"

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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);
	// glFrontFace(GL_CCW);

	DEBUG(" ");

	struct Camera cam = cam_new();
	struct Renderer renderer = ren_new(&cam);

	// struct Line line = line_new((Vec3D){-0.1f, -0.1f, 0.0f}, (Vec3D){-0.8f, -0.8f, 0.0f}, RED, NULL);
	// struct Triangle tri = triangle_new((float[]){0.75f, 0.25f, 0.0f, 0.5f, 0.5f, 0.0f, 0.25f, 0.25f, 0.0f}, BLUE, NULL);
	// struct Quad quad = quad_new((float[]){0.2f, 0.2f, 0.0f, 0.0f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f, -0.5f, 0.0f, 0.0f}, GREEN, NULL);
	struct Primitive xa = prim_new(PRIMITIVE_LINE, (float[]){-1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, RED);
	struct Primitive ya = prim_new(PRIMITIVE_LINE, (float[]){0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f}, GREEN);
	struct Primitive za = prim_new(PRIMITIVE_LINE, (float[]){0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f}, BLUE);
	struct Primitive tri = prim_new(PRIMITIVE_TRIANGLE, (float[]){ 0.5f, 0.1f, 0.0f, 0.1f, 1.0f, 0.0f, -0.5f, 0.1f, 0.0f }, WHITE);
	// struct Primitive quad = prim_new(PRIMITIVE_QUAD, (float[]){0.3f, 0.0f, 1.0f, 0.3f, 0.3f, 1.0f, 0.0f, 0.3f, 1.0f, 0.0f, 0.0f, 1.0f}, GREEN);
	ren_add_prim(&renderer, &xa);
	ren_add_prim(&renderer, &ya);
	ren_add_prim(&renderer, &za);
	ren_add_prim(&renderer, &tri);
	// ren_add_prim(&renderer, &quad);

	DEBUG("\n\tBeginning main loop\n"
	  "-----------------------------------");
	uint32 ntime, otime = 0;
	uint32 bank = 0;
	double dt;
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
						// case SDLK_a: cam.pos[0] -= cam.speed * dt; DEBUG("SDLK_a: %f", cam.pos[0]); break;
						// case SDLK_d: cam.pos[0] += cam.speed * dt; DEBUG("SDLK_d: %f", cam.pos[0]); break;
						// case SDLK_w: cam.pos[2] -= cam.speed * dt; DEBUG("SDLK_w: %f", cam.pos[2]); break;
						// case SDLK_s: cam.pos[2] += cam.speed * dt; DEBUG("SDLK_s: %f", cam.pos[2]); break;
						// case SDLK_LEFT : cam.yaw += cam.speed * dt * 30.0f; DEBUG("SDLK_LEFT: %f", cam.yaw); break;
						// case SDLK_RIGHT: cam.yaw -= cam.speed * dt * 30.0f; DEBUG("SDLK_RIGHT: %f", cam.yaw); break;
						// case SDLK_UP   : cam.yaw += cam.speed * dt * 30.0f; DEBUG("SDLK_LEFT: %f", cam.yaw); break;
						// case SDLK_DOWN : cam.yaw -= cam.speed * dt * 30.0f; DEBUG("SDLK_RIGHT: %f", cam.yaw); break;
						case SDLK_a: cam_move_ortho(&cam, dt, DIR_LEFT)    ; break;
						case SDLK_d: cam_move_ortho(&cam, dt, DIR_RIGHT)   ; break;
						case SDLK_q: cam_move_ortho(&cam, dt, DIR_UP)      ; break;
						case SDLK_e: cam_move_ortho(&cam, dt, DIR_DOWN)    ; break;
						case SDLK_w: cam_move_ortho(&cam, dt, DIR_FORWARD) ; break;
						case SDLK_s: cam_move_ortho(&cam, dt, DIR_BACKWARD); break;
						case SDLK_LEFT : cam_rotate_ortho(&cam, dt, DIR_LEFT) ; break;
						case SDLK_RIGHT: cam_rotate_ortho(&cam, dt, DIR_RIGHT); break;
						case SDLK_UP   : cam_rotate_ortho(&cam, dt, DIR_UP)   ; break;
						case SDLK_DOWN : cam_rotate_ortho(&cam, dt, DIR_DOWN) ; break;
					}
				} else if (event.type == SDL_KEYUP) {

				}
			}
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ren_draw(&renderer);
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
