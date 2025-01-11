#pragma once

#include "../include/object.h"
#include "../../api/include/camera.h"

namespace components {
	class sprite_renderer : public object::base_component {
	public:
		api::shader sd;

		~sprite_renderer();
		sprite_renderer();
		sprite_renderer(api::camera* camera);
		void updateGameObj() override;
		void update() override;
		std::string toString() override;
	private:
		std::vector<glm::vec2> drawable_square;
		components::transform* tr;
		components::sprite* sp;
		api::camera* camera;
		GLuint VBO, VAO, EBO;
	};
}