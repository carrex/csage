#include "maths/maths.h"
#include "primitives.h"
#include "camera.h"

struct Camera cam_new()
{
	struct Camera cam = {
		.speed   = 1.0f,
		.pitch   = (float)PI/2.0f,
		.yaw     = 0.0f,
		.pos     = { 1.0f, 1.0f, 1.0f },
		.up      = { 0.0f, 1.0f, 0.0f },
		.right   = { 1.0f, 0.0f, 0.0f },
		.worldup = { 0.0f, 1.0f, 0.0f },
	};
	cam_calc_view(&cam);
	cam_calc_proj(&cam);

	return cam;
}

void cam_calc_view(struct Camera* cam)
{
	float* trans = I4;
	float* rot   = I4;
	Vec3D pos;
	vec_copy_3d(pos, cam->pos);
	vec_mul_3d(pos, (double)(-1));
	mat_translate(trans, cam->pos, 4);
	mat_rotate(rot, -cam->yaw, 4, Y_AXIS);
	mat_multiply(trans, rot, cam->view, 4, 4);
	mat_print(trans, 4);
	mat_print(rot, 4);
	mat_print(cam->view, 4);
}

void cam_calc_proj(struct Camera* cam)
{
	float near   = 0.1f;
	float far    = 100.0f;
	float fov    = (float)radians(65.0);
	float aspect = 1280.0f / 720.0f;
	float range  = (float)tan(fov * 0.5f) * near;
	float sx = (2.0f * near) / (range * aspect + range * aspect); // -->!
	float sy = near / range;
	float sz = -(far + near) / (far - near);
	float pz = -(2.0f * far * near) / (far - near);
	Mat4x4 proj = { sx  , 0.0f, 0.0f,  0.0f,
	                0.0f, sy  , 0.0f,  0.0f,
	                0.0f, 0.0f, sz  , -1.0f,
	                0.0f, 0.0f, pz  ,  0.0f, };
	mat_copy(cam->proj, proj, 4);
}
