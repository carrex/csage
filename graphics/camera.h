#ifndef CAMERA_H
#define CAMERA_H

enum Projection {
	PROJ_ORTHOGONAL,
	PROJ_PERSPECTIVE,
};

struct Camera {
	Vec3D pos;
	Vec3D front, up, right, worldup;
	float yaw, pitch;
	float speed;
	Mat4x4 proj, view;
};

struct Camera cam_new(void);
void cam_calc_view(struct Camera* cam);
void cam_calc_proj(struct Camera* cam);

#endif
