#include "../include/rigidbody2d.h"

components::rigidbody2d::~rigidbody2d() {}
components::rigidbody2d::rigidbody2d() {}

components::rigidbody2d::rigidbody2d(api::scene* sc, rigidbodyType rbType, int mass, glm::vec2 velocity, float impulse, float maxImpulse, float gravity) {
	this->sc = sc;
	this->rbType = rbType;
	this->mass = mass;
	this->velocity = velocity;
	this->impulse = impulse;
	this->maxImpulse = maxImpulse;
	this->gravity = gravity;
}

void components::rigidbody2d::updateGameObj() {
	this->tr = gameObj->get_component<transform>();
    this->bx = gameObj->get_component<box_collider2d>();
}

void components::rigidbody2d::update() {
    if (rbType == rigidbodyType::DYNAMIC) {
        glm::vec2 pos = tr->getPos();
        if (impulse <= maxImpulse)
            impulse += sc->wnd->deltaTime;
        velocity.y += gravity;
        pos = pos + velocity * impulse * (float)(mass * sc->wnd->deltaTime);
        velocity.y -= gravity;
        tr->setPos(pos);
    }
    for (auto& obj : bx->getAllCollisions()) {
        if (gameObj == obj.gameObj)
            continue;
        if (rbType == rigidbodyType::KINEMATIC)
            continue;
        rigidbody2d* other = obj.gameObj->get_component<rigidbody2d>();
        resolveCollision(other);
    }
}

std::string components::rigidbody2d::toString() {
	return std::string("rigidbody2d");
}

void components::rigidbody2d::applyForce(glm::vec2 force) {
	this->velocity = this->velocity + force;
	this->impulse = 0;
}

int components::rigidbody2d::resolveCollision(rigidbody2d* other) {
    if (this->rbType == rigidbodyType::STATIC)
        return 0;

    int colDir = 0;

    transform* B = other->gameObj->get_component<transform>();
    transform* A = this->tr;

    collision2d col = this->bx->getCollision();

    glm::vec2 minAxis;
    double minOverlap;

    if (this->bx->detectCollisionOverlap(B, minAxis, minOverlap)) {
        glm::vec2 separationVector = minAxis * (float)(minOverlap / 2);

        separationVector = glm::abs(separationVector);

        if (separationVector.y >= 1) {
            this->impulse = 0;
            separationVector = glm::vec2(separationVector.x, 0.5f);
        }
        if (separationVector.x >= 1) {
            this->impulse = 0;
            separationVector = glm::vec2(0.5f, separationVector.y);
        }

        if (A->getPos().y < B->getPos().y)
            separationVector.y = -separationVector.y;

        if (A->getPos().x < B->getPos().x)
            separationVector.x = -separationVector.x;

        this->impulse = 0;
        A->setPos(A->getPos() + separationVector);
        if (other->rbType == rigidbodyType::DYNAMIC)
            B->setPos(B->getPos() - separationVector);

        glm::vec2 relativeVelocity = (other->velocity - velocity);
        double velocityAlongNormal = glm::dot(relativeVelocity, minAxis);

        if (velocityAlongNormal < 0) {
            double restitution = 0.8;
            double impulseScalar = -(1 + restitution) * velocityAlongNormal;
            glm::vec2 impulse = (minAxis * (float)impulseScalar);

            velocity = (velocity + (impulse * 0.5f));
            other->velocity = (other->velocity + (impulse * 0.5f));
        }
    }

    return colDir;
}