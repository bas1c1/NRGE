#pragma once

#include <GL/glew.h>

#include "../api.h"
#include "../../components/include/object.h"
#include "../../utils/utils.h"
#include "../include/shader.h"
#include "../include/camera.h"
#include "../include/window.h"

namespace api {
	class scene {
	public:
		camera* camera;
		window* wnd;

		~scene();
		scene();
		scene(window *wnd, api::camera *camera);
		void renderScene();
		void addObject(components::object* obj);
		components::object* getObject(int index);
		components::object* getObjectByName(std::string name);
		std::vector<std::string> getObjectNameList();
		std::vector<components::object*> getObjects();
	private:
		std::vector<components::object*> objects;
		shader screen_shader;

		void sortByLayers();
	};
}