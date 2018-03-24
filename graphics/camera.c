#include "maths/maths.h"
#include "primitives.h"
#include "camera.h"

struct Camera cam_new()
{
	struct Camera cam = {
		.projection = PROJ_PERSPECTIVE,
		.speed      = 0.05f,
		.pitch      = 90.0f,
		.yaw        = 0.0f,
		.pos        = { 0.0f, 0.0f, 2.0f },
		.up         = { 0.0f, 1.0f, 0.0f },
		.right      = { 1.0f, 0.0f, 0.0f },
		.worldup    = { 0.0f, 0.0f, 1.0f },
	};
	cam_calc_view(&cam);
	cam_calc_proj(&cam);

	return cam;
}

void cam_calc_view(struct Camera* cam)
{
	float trans[16] = I4;
	float f[3] = { -cam->pos[0], -cam->pos[1], -cam->pos[2] };
	mat_translate(trans, f, 4);
	vec_norm_3d(f);
	float u[3]; vec_copy_3d(u, cam->up);
	float r[3]; vec_cross(r, f, u);
	float rot[16] = { r[0], r[1], r[2], cam->pos[0],
	                  u[0], u[1], u[2], cam->pos[1],
	                  f[0], f[1], f[2], cam->pos[2],
	                   0.0f,  0.0f,  0.0f, 1.0f};
	// float rot[16] = { 1.0f, 0.0f,  0.0f,  0.0f,
	//                   0.0f, 1.0f, -1.0f,  0.0f,
	//                   0.0f, 1.0f,  0.0f,  0.0f,
	//                   0.0f, 0.0f,  0.0f,  1.0f, };
	mat_transpose(rot, 4);
	

	// float trans[16] = I4;
	// mat_translate(trans, (float[]){ -cam->pos[0], -cam->pos[1], -cam->pos[2] }, 4);
	
	// float rot[16] = I4;
	// mat_rotate(rot, -(float)radians(cam->yaw), 4, Y_AXIS);
	
	mat_multiply(cam->view, rot, trans, 4);
	// mat_print(trans, 4);
	// mat_print(rot, 4);
	// DEBUG("View: ");
	// mat_print(cam->view, 4);
}

void cam_calc_proj(struct Camera* cam)
{
	float sx, sy, sz, sw, pz;
	float f =  100.0f;
	float n =  1.0f;
	float r =  1280.0f/2.0f;
	float l = -1280.0f/2.0f;
	float t =  720.0f/2.0f;
	float b = -720.0f/2.0f;
	float fov    = radians(67.0f);
	float aspect = 1280.0f / 720.0f;
	float range  = (float)tan(fov/2.0f) * n;
	if (cam->projection == PROJ_PERSPECTIVE) {
		sx = (2.0f * n) / (range * aspect + range * aspect); // -->!
		sy = n / range;
		sz = -(f + n) / (f - n);
		// sx = n / (1280.0f/2.0f);
		// sy = n / (720.0f/2.0f);
		// sz = -(f + n) / (f - n);
		sw = 0.0f;
		pz = -((2.0f * f * n) / (f - n));
	} else if (cam->projection == PROJ_ORTHOGONAL) {
		// sx =  1.0f / (1280.0f/2.0f);
		// sy =  1.0f / (720.0f/2.0f);
		// sz = -2.0f / (far - near);
		// sw = 1.0f;
		// pz = -(far + near) / (far - near);
	} else {
		ERROR("[GFX] No valid projection type set");
		return;
	}
	
	// sy = 1.0f/(float)tan(radians(67.0/2.0));
	// sx = sy / aspect;
	// sz = -((f+n) / (f-n));
	// float proj[16] = { sx  , 0.0f,  0.0f, 0.0f,
	//                    0.0f, sy  ,  0.0f, 0.0f,
	//                    0.0f, 0.0f,  sz  , pz  ,
	//                    0.0f, 0.0f, -1.0f, sw  , };
	float proj[16] = { 1.0f, 0.0f,  0.0f,  0.0f,
	                   0.0f, 1.0f,  0.0f,  0.0f,
	                   0.0f, 0.0f,  1.0f,  0.0f,
	                   0.0f, 0.0f,  0.0f,  1.0f, };
	mat_copy(cam->proj, proj, 4);
	// DEBUG("Projection: ");
	// mat_print(cam->proj, 4);
	// float a[16];
	// mat_multiply(a, cam->view, cam->proj, 4);
	// mat_print(a, 4);
}
