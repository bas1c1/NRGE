#include "../include/scene.h"

api::scene::~scene() {};
api::scene::scene() { this->camera = nullptr; };

api::scene::scene(window* wnd, api::camera* camera) {
	this->objects = std::vector<components::object*>();
	this->camera = camera;
	this->wnd = wnd;
	this->screen_shader = shader("C:\\Users\\Roman\\source\\repos\\NewEngine2D\\Release\\shaders\\screen.vs", "C:\\Users\\Roman\\source\\repos\\NewEngine2D\\Release\\shaders\\screen.fs");
}

void api::scene::renderScene() {
	glBindFramebuffer(GL_FRAMEBUFFER, wnd->framebuffer);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& obj : objects)
		obj->update();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	screen_shader.use();

	this->camera->look(screen_shader);

	glBindVertexArray(wnd->quadVAO);
	glBindTexture(GL_TEXTURE_2D, wnd->textureColorbuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void api::scene::addObject(components::object* obj) {
	objects.push_back(obj);
	sortByLayers();
}

components::object* api::scene::getObject(int index) {
	return objects[index];
}

components::object* api::scene::getObjectByName(std::string name) {
	for (auto& obj : objects) {
		if (obj->name == name)
			return obj;
	}
	return nullptr;
}

std::vector<std::string> api::scene::getObjectNameList() {
	std::vector<std::string> tmp = std::vector<std::string>();
	for (auto& a : objects) {
		tmp.push_back(a->name);
	}
	return tmp;
}

std::vector<components::object*> api::scene::getObjects() {
	return objects;
}

void api::scene::sortByLayers() {
	for (int i = 0; i < objects.size(); i++) {
		for (int j = 0; j < objects.size(); j++) {
			if (j == 0)
				continue;
			if (objects[j]->get_layer() < objects[j - 1]->get_layer())
				std::swap(objects[j], objects[j - 1]);
		}
	}
	std::reverse(objects.begin(), objects.end());
}