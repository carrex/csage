#include "common.h"
#include "config.h"
#include "resourcemanager.h"
#include "gfx/renderer.h"
#include "scenemanager.h"

static struct Renderer* renderer;
static struct Scene scenes[MAX_SCENES];

void scene_init(struct Renderer* ren)
{
	renderer = ren;
	for (int i = 0; i < MAX_SCENES; i++)
		scenes[i].id = 0;
}

uint8 scene_new(char* fname)
{
	struct Scene scene;
	scene.id = 0;
	while (!(scenes[scene.id].id)) scene.id++;

	/* Load from fname */
	// char* file = resource_load_file(fname);

	return scene.id;
}

void scene_update(double dt)
{

}
