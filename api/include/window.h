#pragma once

#include <GL/glew.h>


#include "../api.h"
#include "../include/shader.h"
#include "../include/camera.h"
#include "../../utils/include/logger.h"

//#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace api {
	class window {
	public:
		unsigned int quadVAO;
		unsigned int textureColorbuffer;
		unsigned int rbo;
		unsigned int framebuffer;

		typedef void (*displayf)(void);
		int width, height = 0;
		const char* name;

		float deltaTime = 1.f;
		
		window();
		~window();
		void createWindow(int width, int height, const char *name, GLFWmonitor* monitor, GLFWwindow* share, float camera_zoom = 1.f);
		void run(displayf displayfunc);
	private:
		long nViewW, nViewH, nViewX, nViewY = 0;
		GLFWwindow* glfw_window;

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void processInput(GLFWwindow* window);
		void updateFramebuffer();
	};
}