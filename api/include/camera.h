#pragma once

#include "../api.h"
#include "../include/shader.h"

#include <glm/glm.hpp>

namespace api {
	class camera {
	public:
		shader default_shader;
		glm::vec2 camera_size;
		glm::vec2 camera_pos;
		float zoom;

		camera();
		camera(glm::vec2 camera_size, glm::vec2 camera_pos, float zoom);
		~camera();

		void init();
		void look(shader s);
		glm::vec2 project(glm::vec2 pos);
	private:
	};
}