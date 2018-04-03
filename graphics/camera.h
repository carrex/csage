#ifndef CAMERA_H
#define CAMERA_H

enum Projection {
	PROJ_ORTHOGONAL,
	PROJ_PERSPECTIVE,
};

struct Camera {
	enum Direction movedir, rotatedir;

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
void camera_set_move(bool set, struct Camera* cam, enum Direction dir);
void camera_move(struct Camera* cam, float dt);
void camera_set_rotate(struct Camera* cam, bool set, enum Direction dir);
// void camera_rotate(struct Camera* cam, float dt);
void camera_update(struct Camera* cam, float dt);

#endif
