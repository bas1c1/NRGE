#include "../include/sprite_batching.h"
#include <glm/glm.hpp>

#define SCREEN_TO_NDC(v) (glm::vec2(v.x / this->camera->camera_size.x * 2 - 1, v.y / this->camera->camera_size.y * 2 - 1))

api::sprite_batching::~sprite_batching() {}
api::sprite_batching::sprite_batching() {}

api::sprite_batching::sprite_batching(api::camera *camera, components::sprite *sp) {
    this->frames = std::vector<sprite_frame>();
    this->camera = camera;
    this->sp = sp;
    this->sd = camera->default_shader;
    this->texture = sp->gpuTexture;
    this->vaos = std::vector<GLfloat>();
    this->indices = new GLuint[6];
}

GLuint api::sprite_batching::getTexture() {
    return this->texture;
}

void api::sprite_batching::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 32 * 10000, 0, GL_DYNAMIC_DRAW);

    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
}

void api::sprite_batching::setTexture(GLuint texture) {
    this->texture = texture;
}

std::vector<api::sprite_frame> api::sprite_batching::getFrames() {
    return this->frames;
}

api::sprite_frame api::sprite_batching::getFrame(int index) {
    return this->frames[index];
}

void api::sprite_batching::setFrame(int index, api::sprite_frame frame) {
    this->frames[index] = frame;
}

void api::sprite_batching::pushFrame(api::sprite_frame frame) {
    this->frames.push_back(frame);
#define p(arg) this->vaos.push_back(arg);
    glm::vec2 posF = camera->project({ static_cast<float>(frame.x), static_cast<float>(frame.y) });

    std::vector<glm::vec2> s = std::vector<glm::vec2>{
        SCREEN_TO_NDC(glm::vec2((posF.x), (posF.y))),
        SCREEN_TO_NDC(glm::vec2((posF.x), (posF.y + frame.height))),
        SCREEN_TO_NDC(glm::vec2((posF.x + frame.width), (posF.y + frame.height))),
        SCREEN_TO_NDC(glm::vec2((posF.x + frame.width), (posF.y)))
    };

    p(s[3].x); p(s[3].y); p(0);   p(1.0f); p(0.0f); p(0.0f);   p(1.0f); p(1.0f);
    p(s[2].x); p(s[2].y); p(0);   p(0.0f); p(1.0f); p(0.0f);   p(1.0f); p(0.0f);
    p(s[1].x); p(s[1].y); p(0);   p(0.0f); p(0.0f); p(1.0f);   p(0.0f); p(0.0f);
    p(s[0].x); p(s[0].y); p(0);   p(1.0f); p(1.0f); p(0.0f);   p(0.0f); p(1.0f);

    s.clear();
#undef p(arg)

    //delete[] indices;
    //indices = new GLuint[(this->vaos.size()) * 6];
}

void api::sprite_batching::clearBuffers() {
    this->vaos.clear();
    this->frames.clear();
}

void api::sprite_batching::render() {
    this->sd.use();

    std::vector<GLuint> indices(this->vaos.size() * 6);
    unsigned int j = 0;
    for (unsigned int i = 0; i < this->vaos.size() * 6; i += 6, j += 4) {
        indices[i] = j;
        indices[i + 1] = j + 1;
        indices[i + 2] = j + 2;
        indices[i + 3] = j + 2;
        indices[i + 4] = j + 3;
        indices[i + 5] = j;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, this->vaos.size() * sizeof(GLfloat), this->vaos.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 2, indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, this->texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

    indices.clear();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDeleteBuffers(1, &EBO);

    /*unsigned int j = 0;
    for (unsigned int i = 0; i < this->vaos.size() * 6; i += 6, j += 4) {
        indices[i] = j;
        indices[i + 1] = j + 1;
        indices[i + 2] = j + 2;
        indices[i + 3] = j + 2;
        indices[i + 4] = j + 3;
        indices[i + 5] = j;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, this->vaos.size() * sizeof(GLfloat), this->vaos.data());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (this->vaos.size()) * 6 * 2, indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, this->texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (this->vaos.size()) * 6, GL_UNSIGNED_INT, indices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDeleteBuffers(1, &EBO);*/
}