#pragma once

#include "../include/object.h"
#include "../../utils/utils.h"
#include "../../utils/include/logger.h"
#include <GL/glew.h>

namespace components {
	struct image2d {
		int width, height, nrChannels;
		unsigned char* pixels;
	};

	image2d gen_img(std::string path);

	class sprite : public object::base_component {
	public:
		image2d img;
		GLuint gpuTexture;

		~sprite();
		sprite();
		sprite(int width, int height);
		sprite(int width, int height, unsigned char* pixels);

		void from_img(image2d img);
		image2d from_png(std::string path);
		void generateGpuTexture();
		void updateGpuTexture();
	private:
	};
}