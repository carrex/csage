#ifndef CAMERA_H
#define CAMERA_H

enum Projection {
	PROJ_ORTHOGONAL,
	PROJ_PERSPECTIVE,
};

struct Camera {
	enum Projection projection;
	float pos[3];
	float front[3], up[3], right[3], worldup[3];
	float yaw, pitch; // In degrees
	float speed;
	float proj[16], view[16];
};

struct Camera cam_new(void);
void cam_calc_view(struct Camera* cam);
void cam_calc_proj(struct Camera* cam);

#endif
