#include "maths/maths.h"
#include "primitives.h"
#include "camera.h"

struct Camera camera_new()
{
	struct Camera cam = {
		.projection = PROJ_PERSPECTIVE,
		.speed      = 100.0f,
		.pitch      = 0.0f,
		.yaw        = 0.0f,
		.pos        = { 0.0f, 0.0f,  50.0f },
		.front      = { 0.0f, 0.0f, -1.0f },
		.up         = { 0.0f, 1.0f,  0.0f },
		.right      = { 1.0f, 0.0f,  0.0f },
		.fov        = (float)radians(67.0),
		.aspect     = 16.0f / 9.0f,
		.near       = 0.1f,
		.far        = 100.0f,
	};
	matrix_copy(cam.view, I4, 4);
	matrix_copy(cam.proj, I4, 4);
	matrix_translate_sub(cam.view, cam.pos);
	matrix_perspective(cam.proj, cam.fov, cam.aspect, cam.near, cam.far);

	return cam;
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
	matrix_translate(cam->view, (float[]){ -cam->pos[0], -cam->pos[1], -cam->pos[2] });
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

