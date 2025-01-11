#include "../include/window.h"

api::window::window() { this->glfw_window = nullptr; }
api::window::~window() {}

void api::window::createWindow(int width, int height, const char* name, GLFWmonitor* monitor, GLFWwindow* share, float camera_zoom) {
    this->width = width;
    this->height = height;
    this->name = name;

    if (!glfwInit())
        utils::logger::critical(std::string("GLFW cannot initialize"));

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfw_window = glfwCreateWindow(width, height, name, monitor, share);
        
    if (!glfw_window)
    {
        glfwTerminate();
        utils::logger::critical(std::string("GLFW cannot create window"));
    }

    glfwMakeContextCurrent(glfw_window);
    glewExperimental = GL_TRUE;
    glewInit();
    glfwSetWindowUserPointer(glfw_window, this);
    glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);

    //glfwSwapInterval(1);
}

void api::window::run(displayf displayfunc) {
    float quadVertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    unsigned int quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    updateFramebuffer();

    glfwSwapInterval(60);
    static auto start = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    auto ct = std::chrono::duration<double>(now - start).count();

    double lastFrameTime = ct;

    while (!glfwWindowShouldClose(glfw_window))
    {
        static auto start = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();
        auto ct = std::chrono::duration<double>(now - start).count();

        double currentTime = ct;
        deltaTime = 10*(currentTime - lastFrameTime);
        lastFrameTime = currentTime;

        srand((unsigned int)clock());

        processInput(glfw_window);

        displayfunc();

        glfwSwapBuffers(glfw_window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void api::window::processInput(GLFWwindow* glfw_window) {
    if (glfwGetKey(glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfw_window, true);
}

void api::window::framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height) {
    window* obj = reinterpret_cast<window*>(glfwGetWindowUserPointer(glfw_window));

    glViewport(0, 0, width, height);
    obj->width = width;
    obj->height = height;
    obj->updateFramebuffer();
}

void api::window::updateFramebuffer() {
    glDeleteTextures(1, &textureColorbuffer);
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDeleteRenderbuffers(1, &rbo);
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glDeleteFramebuffers(1, &framebuffer);
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        utils::logger::critical("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}