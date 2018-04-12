#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "common.h"
#include "maths/maths.h"
#include "graphics/graphics.h"
#include "resourcemanager.h"
#include "eventmanager.h"
#include "config.h"
#include "csage.h"

#include "game.h"

SDL_Window* window;
SDL_GLContext context;
struct Renderer renderer;
struct Camera camera;

int main(int argc, char** argv)
{
	(void)argc; (void)argv;
	NimMain();
	DEBUG("[INIT] Nim initialized");

	csage_init();
	init();
	csage_loop();
}

void csage_init()
{
	DEBUG("\t=== === === %s === === ===", WINDOW_TITLE);
	struct Config const config = {
		.windoww = 1280,
		.windowh = 720,
	};

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		                      config.windoww, config.windowh, SDL_WINDOW_OPENGL);
	if (window)
		DEBUG("[INIT] SDL initialized");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glViewport(0, 0, config.windoww, config.windowh);

	context = SDL_GL_CreateContext(window);
	if (context)
		DEBUG("[INIT] OpenGL context created: version %s", glGetString(GL_VERSION));
	SDL_GL_SetSwapInterval(0);

	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK)
		DEBUG("[INIT] GLEW initialized: version %s", glewGetString(GLEW_VERSION));
	glGetError(); // Glew bug creates an INVALID_ENUM on init

	DEBUG("%s", openblas_get_config());

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

	camera   = camera_new(128.0f, 100.0f, 67.0f, PROJ_PERSPECTIVE);
	renderer = renderer_new(&camera);

	em_register_key(SDLK_ESCAPE, CB_NONE, (VoidFn)csage_quit, 0, 0, 0);
	em_register_key(SDLK_w, CB_KDOWN_DATA2, (VoidFn)camera_set_move, 0, (intptr)&camera, DIR_FORWARD);
	em_register_key(SDLK_a, CB_KDOWN_DATA2, (VoidFn)camera_set_move, 0, (intptr)&camera, DIR_LEFT);
	em_register_key(SDLK_s, CB_KDOWN_DATA2, (VoidFn)camera_set_move, 0, (intptr)&camera, DIR_BACKWARD);
	em_register_key(SDLK_d, CB_KDOWN_DATA2, (VoidFn)camera_set_move, 0, (intptr)&camera, DIR_RIGHT);
	em_register_key(SDLK_q, CB_KDOWN_DATA2, (VoidFn)camera_set_move, 0, (intptr)&camera, DIR_UP);
	em_register_key(SDLK_e, CB_KDOWN_DATA2, (VoidFn)camera_set_move, 0, (intptr)&camera, DIR_DOWN);
	// em_register_key(SDLK_RIGHT, CB_KDOWN_DATA2, (VoidFn)camera_set_rotate, 0, (intptr)&camera, DIR_RIGHT);
}

void csage_loop()
{
	struct Sprite s  = sprite_new((float[]){  32.0, -32.0, 0 }, (float[]){ 32 , 32 , 0 }, GFX_DIR "kitties.tga");
	// struct Sprite s2 = sprite_new((float[]){ -1.0 , -1.0 , 0 }, (float[]){ 0.5, 0.5, 0 }, ASSET_DIR "test.jpg");
	// struct Line line = line_new((Vec3D){-0.1f, -0.1f, 0.0f}, (Vec3D){-0.8f, -0.8f, 0.0f}, RED, NULL);
	// struct Triangle tri = triangle_new((float[]){0.75f, 0.25f, 0.0f, 0.5f, 0.5f, 0.0f, 0.25f, 0.25f, 0.0f}, BLUE, NULL);
	// struct Quad quad = quad_new((float[]){0.2f, 0.2f, 0.0f, 0.0f, 0.5f, 0.0f, -0.5f, 0.5f, 0.0f, -0.5f, 0.0f, 0.0f}, GREEN, NULL);
	struct Primitive xa = prim_new(PRIMITIVE_LINE, (float[]){ -1280.0f, 0.0f, 0.0f, 1280.0f, 0.0f, 0.0f }, RED);
	struct Primitive ya = prim_new(PRIMITIVE_LINE, (float[]){ 0.0f, -720.0f, 0.0f, 0.0f, 720.0f, 0.0f }, GREEN);
	struct Primitive za = prim_new(PRIMITIVE_LINE, (float[]){ 0.0f, 0.0f, -720.0f, 0.0f, 0.0f, 720.0f }, BLUE);
	// struct Texture tex = tex_new("tex.jpg");
	// float tpos[] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };
	// struct Primitive tri = prim_new(PRIMITIVE_TRIANGLE, (float[]){ 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -0.5f, 0.0f, 0.0f }, NULL,
	// 	                            &tex, tpos);
	struct Primitive quad1 = prim_new(PRIMITIVE_QUAD, (float[]){0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 50.f, -50.f, 50.f, 50.f, -50.f, 50.f, 0.0f}, RED);
	struct Primitive quad2 = prim_new(PRIMITIVE_QUAD, (float[]){0.0f, 0.0f, 0.0f, 50.f, 0.0f, 0.0f, 50.f, 50.f, 0.0f, 0.0f, 50.f, 0.0f}, GREEN);
	struct Primitive quad3 = prim_new(PRIMITIVE_QUAD, (float[]){0.0f, 0.0f, 0.0f, 0.0f, -30.f, 0.0f, -30.f, -30.f, 0.0f, -30.f, 0.0f, 0.0f}, BLUE);
	renderer_add_prim(&renderer, &xa);
	renderer_add_prim(&renderer, &ya);
	renderer_add_prim(&renderer, &za);
	// renderer_add_prim(&renderer, &tri);
	renderer_add_prim(&renderer, &quad1);
	renderer_add_prim(&renderer, &quad2);
	renderer_add_prim(&renderer, &quad3);
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
		bank += dt;
		dt   *= 1.0e-3;
		while (bank >= LOGIC_FPS) {
			bank -= LOGIC_FPS;

			em_update(dt);
			update(dt);
			camera_update(&camera, dt);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer_draw(&renderer);
		SDL_GL_SwapWindow(window);

		csage_quit();
	}
}

noreturn void csage_quit()
{
	DEBUG("Exiting...");

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	exit(0);
}
