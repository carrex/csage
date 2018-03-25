#include "maths/maths.h"
#include "primitives.h"
#include "camera.h"

struct Camera cam_new()
{
	struct Camera cam = {
		.projection = PROJ_PERSPECTIVE,
		.speed      = 100.0f,
		.pitch      = 0.0f,
		.yaw        = 0.0f,
		.pos        = { 0.0f, 0.0f,  2.0f },
		.front      = { 0.0f, 0.0f, -1.0f },
		.up         = { 0.0f, 1.0f,  0.0f },
		.right      = { 1.0f, 0.0f,  0.0f },
		.fov        = radians(67.0f),
		.aspect     = 16.0f / 9.0f,
		.near       = 0.1f,
		.far        = 100.0f,
	};
	quat_new_versor(cam.dir, 0.0f, 0.0f, 0.0f, -1.0f);
	mat_new_perspective(cam.proj, cam.fov, cam.aspect, cam.near, cam.far);
	cam_lookat(&cam);

	return cam;
}

void cam_lookat(struct Camera* cam)
{
	mat_new_lookat(cam->view, (float[])VEC3D_ZERO, cam->up, cam->pos);
}

void cam_move_ortho(struct Camera* cam, double dt, enum Direction dir)
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
	cam_lookat(cam);
}

void cam_rotate_ortho(struct Camera* cam, double dt, enum Direction dir)
{
	float vel = cam->speed / 10.0f * dt;
	switch (dir) {
		case DIR_RIGHT: cam->yaw   -= vel; break;
		case DIR_LEFT : cam->yaw   += vel; break;
		case DIR_UP   : cam->pitch -= vel; break;
		case DIR_DOWN : cam->pitch += vel; break;
		default: ERROR("Invalid Direction");
	}

	cam_lookat(cam);
	// mat_print(cam->view , 4);
}

