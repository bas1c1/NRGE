#include "../include/camera.h"

#define FASTPROJECTX(x, width)  x + width /  2
#define FASTPROJECTY(y, height) y + height / 2

api::camera::camera() {
	this->camera_size = glm::vec2();
	this->camera_pos = glm::vec2();
	this->zoom = 1;
}

api::camera::camera(glm::vec2 camera_size, glm::vec2 camera_pos, float zoom) {
	this->camera_size = camera_size;
	this->camera_pos = camera_pos;
	this->zoom = zoom;
}

void api::camera::init() {
	this->default_shader = api::shader("shaders\\default.vs", "shaders\\default.fs");
}

api::camera::~camera() {}

void api::camera::look(shader s) {
	s.setFloat("scale", zoom);
}

glm::vec2 api::camera::project(glm::vec2 pos) {
	return glm::vec2(FASTPROJECTX(pos.x, camera_size.x), FASTPROJECTX(pos.y, camera_size.y));
}