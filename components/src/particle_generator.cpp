#include "../include/particle_generator.h"

components::particle_generator::~particle_generator() {}
components::particle_generator::particle_generator() {}

components::particle_generator::particle_generator(api::scene* sc, int amount, glm::vec2 defaultSize, glm::vec2 defaultVelocity, float defaultLifetime, glm::vec2 pos) {
    this->sc = sc;
    this->amount = amount;
    this->defaultSize = defaultSize;
    this->defaultVelocity = defaultVelocity;
    this->defaultLifetime = defaultLifetime;
    this->pos = pos;
}

void components::particle_generator::updateGameObj() {
    this->sp = gameObj->get_component<sprite>();
    this->tr = gameObj->get_component<transform>();
    this->sp->generateGpuTexture();
    this->spb = api::sprite_batching(this->sc->camera, this->sp);
    spb.init();
    for (int i = 0; i < amount; i++) {
        particle_frame pf;
        this->particles.push_back(pf);
    }
}

api::sprite_frame spf;

void components::particle_generator::update() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    int i = 0;
    for (particle_frame& particle : this->particles) {
        spf.height = defaultSize.y;
        spf.width = defaultSize.x;
        spf.x = particle.pos.x;
        spf.y = particle.pos.y;
        if (particle.life > 0.0f) {
            particle.life -= sc->wnd->deltaTime;
            float random = ((rand() % 100) - 50) / 10.0f;
            float random2 = ((rand() % 100) - 50) / 10.0f;
            particle.pos.x += random * defaultVelocity.x * sc->wnd->deltaTime * 10;
            particle.pos.y += random2 * defaultVelocity.y * sc->wnd->deltaTime * 10;
            spf.x = particle.pos.x;
            spf.y = particle.pos.y;
        }
        else {
            particle.life = defaultLifetime * sc->wnd->deltaTime;
            particle.pos = this->tr->getPos() + this->pos;

        }
        spb.pushFrame(spf);
        i += 1;
    }

    spb.render();
    spb.clearBuffers();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

std::string components::particle_generator::toString() {
    return std::string("particle_generator");
}