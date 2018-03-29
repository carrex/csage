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
		.speed      = 50.0f,
		.pitch      = 0.0f,
		.yaw        = 0.0f,
		.pos        = { 1750.0f, -300.0f, 4800.0f },
		.front      = { 0.0f, 0.0f, -1.0f },
		.up         = { 0.0f, 1.0f,  0.0f },
		.right      = { 1.0f, 0.0f,  0.0f },
		.view       = { 0 },
		.proj       = { 0 },
	};
	camera_update_view(&cam);
	if (proj == PROJ_PERSPECTIVE)
		mat4_new_perspective(cam.proj, scalex/scaley, (float)radians(fovy), 0.01f, 1200.0f);
	else if (proj == PROJ_ORTHOGONAL)
		mat4_new_orthogonal(cam.proj, 0.01f, 10.0f);

	return cam;
}

void camera_update_view(struct Camera* cam)
{
	vec3_print(cam->pos);
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

    mat_print(rot, 4);
	mat4_mul(cam->view, trans, rot);
}

void camera_move_ortho(struct Camera* cam, float dt, enum Direction dir)
{
	float vel = cam->speed * dt;
	switch (dir) {
		case DIR_RIGHT   : cam->pos[0] += vel; break;
		case DIR_LEFT    : cam->pos[0] -= vel; break;
		case DIR_UP      : cam->pos[1] += vel; break;
		case DIR_DOWN    : cam->pos[1] -= vel; break;
		case DIR_FORWARD : cam->pos[2] -= vel; break;
		case DIR_BACKWARD: cam->pos[2] += vel; break;
		default: ERROR("Invalid Direction");
	}
	camera_update_view(cam);
	// mat4_new_translate(cam->view, VEC3_VEC3(-cam->pos));
}

void camera_rotate_ortho(struct Camera* cam, float dt, enum Direction dir)
{
	float vel = cam->speed / 10.0f * dt;
	switch (dir) {
		case DIR_RIGHT: cam->yaw   -= vel; break;
		case DIR_LEFT : cam->yaw   += vel; break;
		case DIR_UP   : cam->pitch -= vel; break;
		case DIR_DOWN : cam->pitch += vel; break;
		default: ERROR("Invalid Direction");
	}

}

