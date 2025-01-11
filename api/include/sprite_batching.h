#pragma once

#include <GL/glew.h>
#include "../api.h"
#include "camera.h"
#include <vector>
#include "../../components/include/sprite.h"

namespace api {
	struct sprite_frame {
		int height, width, x, y;
	};

	class sprite_batching {
	public:
		~sprite_batching();
		sprite_batching();
		sprite_batching(api::camera* camera, components::sprite* sp);

		void init();

		void render();

		void clearBuffers();
		GLuint getTexture();
		void setTexture(GLuint texture);
		std::vector<sprite_frame> getFrames();
		sprite_frame getFrame(int index);
		void pushFrame(sprite_frame frame);
		void setFrame(int index, sprite_frame frame);

	private:
		shader sd;
		components::sprite* sp;
		camera* camera;
		GLuint* indices;
		GLuint VBO, VAO, EBO;
		std::vector<sprite_frame> frames;
		std::vector<GLfloat> vaos;
		GLuint texture;
	};
}