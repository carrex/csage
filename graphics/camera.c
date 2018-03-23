#include "maths/maths.h"
#include "primitives.h"
#include "camera.h"

struct Camera cam_new()
{
	struct Camera cam = {
		.projection = PROJ_PERSPECTIVE,
		.speed      = 1.0f,
		.pitch      = 90.0f,
		.yaw        = 0.0f,
		.pos        = { 0.0f, 0.0f, 1.0f },
		.up         = { 0.0f, 1.0f, 0.0f },
		.right      = { 1.0f, 0.0f, 0.0f },
		.worldup    = { 0.0f, 1.0f, 0.0f },
	};
	cam_calc_view(&cam);
	cam_calc_proj(&cam);

	return cam;
}

void cam_calc_view(struct Camera* cam)
{
	float* trans = I4;
	Vec3D  pos   = { -cam->pos[0], -cam->pos[1], -cam->pos[2] };
	mat_translate(trans, pos, 4);
	
	float* rot = I4;
	mat_rotate(rot, -radians(cam->yaw), 4, Y_AXIS);
	
	mat_multiply(trans, rot, cam->view, 4, 4);
	// mat_print(trans, 4);
	// mat_print(rot, 4);
	// DEBUG("View: ");
	mat_print(cam->view, 4);
}

void cam_calc_proj(struct Camera* cam)
{
	float sx, sy, sz, sw, pz;
	float near   = 1.0f;
	float far    = 100.0f;
	if (cam->projection == PROJ_PERSPECTIVE) {
		float fov    = (float)radians(67.0);
		float aspect = 1280.0f / 720.0f;
		float range  = (float)tan(fov * 0.5f) * near;
		DEBUG("%f, %f, %f", fov, aspect, range);
		sx = (2.0f * near) / (range * aspect + range * aspect); // -->!
		sy = near / range;
		sz = -(far + near) / (far - near);
		DEBUG("%f, %f, %f", sx, sy, sz);
		// sx = near / (1280.0f/2.0f);
		// sy = near / (720.0f/2.0f);
		// sz = -(far + near) / (far - near);
		sw = 0.0f;
		pz = -(2.0f * far * near) / (far - near);
		DEBUG("%f", pz);
	} else if (cam->projection == PROJ_ORTHOGONAL) {
		sx =  1.0f / (1280.0f/2.0f);
		sy =  1.0f / (720.0f/2.0f);
		sz = -2.0f / (far - near);
		sw = 1.0f;
		pz = -(far + near) / (far - near);
	} else {
		ERROR("[GFX] No valid projection type set");
		return;
	}
	
	// sx = 1.0f;
	// sy = 1.0f;
	// sz = 1.0f;
	// sw = 1.0f;
	// pz = 0.0f;
	float proj[] = { sx  , 0.0f,  0.0f,  0.0f,
	                 0.0f, sy  ,  0.0f,  0.0f,
	                 0.0f, 0.0f,  sz  , -1.0f,
	                 0.0f, 0.0f,  pz  ,  sw  , };
	mat_copy(cam->proj, proj, 4);
	DEBUG("Projection: ");
	mat_print(cam->proj, 4);
	Mat4x4 a;
	mat_multiply(cam->view, cam->proj, a, 4, 4);
	mat_print(a, 4);
}
