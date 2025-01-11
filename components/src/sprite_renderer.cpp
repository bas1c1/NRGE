#include "../include/sprite_renderer.h"
#include "../include/transform.h"
#include "../include/sprite.h"

#define SCREEN_TO_NDC(v) (glm::vec2(v.x / this->camera->camera_size.x * 2 - 1, v.y / this->camera->camera_size.y * 2 - 1))

components::sprite_renderer::~sprite_renderer() {}
components::sprite_renderer::sprite_renderer() {}

components::sprite_renderer::sprite_renderer(api::camera* camera) {
	this->camera = camera;
    this->sd = camera->default_shader;
    this->drawable_square = std::vector<glm::vec2>(4);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void components::sprite_renderer::updateGameObj() {
    this->tr = this->gameObj->get_component<transform>();
    this->sp = this->gameObj->get_component<sprite>();
}

void components::sprite_renderer::update() {
    this->sd.use();

    drawable_square[0] = SCREEN_TO_NDC(tr->square[0]);
    drawable_square[1] = SCREEN_TO_NDC(tr->square[1]);
    drawable_square[2] = SCREEN_TO_NDC(tr->square[2]);
    drawable_square[3] = SCREEN_TO_NDC(tr->square[3]);

    GLfloat* vertices = new GLfloat[]{
         drawable_square[3].x,  drawable_square[3].y, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         drawable_square[2].x,  drawable_square[2].y, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         drawable_square[1].x,  drawable_square[1].y, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         drawable_square[0].x,  drawable_square[0].y, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };

    GLuint* indices = new GLuint[]{
        0, 1, 3,
        1, 2, 3
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 32, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    delete[] vertices;
    delete[] indices;

    glBindTexture(GL_TEXTURE_2D, this->sp->gpuTexture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

std::string components::sprite_renderer::toString() {
    return std::string("spriteRenderer");
}