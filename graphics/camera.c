#include "maths/maths.h"
#include "primitives.h"
#include "camera.h"

struct Camera camera_new(float scalex, float scaley, float fovy, enum Projection proj)
{
	struct Camera cam = {
		.projection = proj,
		.scalex     = scalex,
		.scaley     = scaley,
		.scalez     = scaley / 2.0f * (float)tan(fovy),
		.mspeed     = 50.0f,
		.rspeed     = 50.0f,
		.pos        = { 1750.0f, -300.0f, 4800.0f },
		.front      = { 0.0f, 0.0f, -1.0f },
		.up         = { 0.0f, 1.0f,  0.0f },
		.right      = { 1.0f, 0.0f,  0.0f },
		.view       = { 0 },
		.proj       = { 0 },
	};
	camera_update_view(&cam);
	if (proj == PROJ_PERSPECTIVE)
		mat4_new_perspective(cam.proj, scalex/scaley, (float)(radians((double)fovy)), 0.01f, 1200.0f);
	else if (proj == PROJ_ORTHOGONAL)
		mat4_new_orthogonal(cam.proj, 0.01f, 10.0f);

	return cam;
}

void camera_update_view(struct Camera* cam)
{
	float trans[16] = { 0 };
	float x = -cam->pos[0] / (float)cam->scalex,
	      y = -cam->pos[1] / (float)cam->scaley,
	      z = -cam->pos[2] / (float)cam->scalez;
	mat4_new_translate(trans, VEC3(x, y, z));

	float* r = cam->right;
	float* u = cam->up;
	float* f = cam->front;
	float rot[16] = {  r[0]/(float)cam->scalex,  r[1],  r[2], 0.0f,
	                   u[0],  u[1]/(float)cam->scaley,  u[2], 0.0f,
	                  -f[0], -f[1], -f[2]/(float)cam->scalez, 0.0f,
	                   0.0f,  0.0f,  0.0f, 1.0f, };

	mat4_mul(cam->view, trans, rot);
}

void camera_set_move(bool set, struct Camera* cam, enum Direction dir)
{
	if (set)
		cam->movedir = dir;
	else if (cam->movedir == dir)
		cam->movedir = DIR_NONE;
}

void camera_move(struct Camera* cam, float dt)
{
	float vel[3];
	vec3_from_dir(vel, cam->movedir);
	// vec3_copy(vel, cam->dir);
	// vec3_scale(vel, cam->mspeed * dt);
	vec3_add(cam->pos, vel, cam->mspeed * dt);

	// float vel = cam->mspeed * dt;
	// switch (cam->movedir) {
	// 	case DIR_RIGHT   : cam->pos[0] += vel; break;
	// 	case DIR_LEFT    : cam->pos[0] -= vel; break;
	// 	case DIR_UP      : cam->pos[1] += vel; break;
	// 	case DIR_DOWN    : cam->pos[1] -= vel; break;
	// 	case DIR_FORWARD : cam->pos[2] -= vel; break;
	// 	case DIR_BACKWARD: cam->pos[2] += vel; break;
	// 	default: ERROR("Invalid Direction");
	// }
	camera_update_view(cam);
}

// void camera_rotate(struct Camera* cam, float dt, enum Direction dir)
// {
// 	float vel = cam->rspeed / 10.0f * dt;
// 	float yaw = 0, pitch = 0;
// 	switch (dir) {
// 		case DIR_RIGHT: yaw   -= vel; break;
// 		case DIR_LEFT : yaw   += vel; break;
// 		case DIR_UP   : pitch -= vel; break;
// 		case DIR_DOWN : pitch += vel; break;
// 		default: ERROR("[GFX] Invalid Direction");
// 	}

// 	camera_update_view(cam);
// }

void camera_update(struct Camera* cam, float dt)
{
	if (cam->movedir)
		camera_move(cam, dt);
}
