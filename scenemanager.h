#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#define MAX_SCENES 4

struct Scene {
	uint8 id;

	int* Entities;
};

void scene_init(struct Renderer* renderer);
uint8 scene_new(char* fname);
void scene_update(double dt);

#endif
