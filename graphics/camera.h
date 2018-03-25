#ifndef CAMERA_H
#define CAMERA_H

enum Projection {
	PROJ_ORTHOGONAL,
	PROJ_PERSPECTIVE,
};

/* Cleanup required later */
struct Camera {
	enum Projection projection;
	float pos[3], dir[4];
	float front[3], up[3], right[3];
	float yaw, pitch;
	float speed;
	float proj[16], view[16];
	float fov;
	float aspect;
	float near, far;
};

struct Camera cam_new(void);
void cam_lookat(struct Camera* cam);
void cam_move_ortho(struct Camera* cam, double dt, enum Direction dir);
void cam_rotate_ortho(struct Camera* cam, double dt, enum Direction dir);

#endif
