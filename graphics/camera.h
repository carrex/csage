#ifndef CAMERA_H
#define CAMERA_H

enum Projection {
	PROJ_ORTHOGONAL,
	PROJ_PERSPECTIVE,
};

struct Camera {
	enum Projection projection;
	float scalex, scaley, scalez;
	float pos[3], dir[4];
	float front[3], up[3], right[3];
	float yaw, pitch;
	float mspeed, rspeed;
	float proj[16], view[16];
	float fov;
	float aspect;
	float near, far;
};

struct Camera camera_new(float scalex, float scaley, float angle, enum Projection proj);
void camera_update_view(struct Camera* cam);
void camera_move_ortho(struct Camera* cam, float dt, enum Direction dir);
void camera_rotate_ortho(struct Camera* cam, float dt, enum Direction dir);

#endif
