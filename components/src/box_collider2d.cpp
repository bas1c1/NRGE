#include "../include/box_collider2d.h"

components::box_collider2d::~box_collider2d() {}
components::box_collider2d::box_collider2d() {}

components::box_collider2d::box_collider2d(api::scene* sc) {
	this->sc = sc;
    this->collision = std::vector<collision2d>();
}

glm::vec2 getEdgeNormal(const glm::vec2& p1, const glm::vec2& p2) {
    glm::vec2 edge = p2 - p1;
    return { -edge.y, edge.x };
}

// Project a shape onto an axis
std::pair<double, double> projectShapeOntoAxis(const components::transform* shape, const glm::vec2& axis) {
    std::vector<double> dots;
    for (const auto& point : shape->square) {
        dots.push_back(glm::dot(point, axis));
    }
    return { *std::min_element(dots.begin(), dots.end()),
            *std::max_element(dots.begin(), dots.end()) };
}

bool projectionsOverlap(const std::pair<double, double>& proj1, const std::pair<double, double>& proj2) {
    return proj1.second >= proj2.first && proj2.second >= proj1.first;
}

bool components::box_collider2d::detectCollisionOverlap(components::transform* obj, glm::vec2& minAxis, double& minOverlap) {
    std::vector<components::transform*> shapes = { this->tr, obj };
    minOverlap = UINT64_MAX;

    for (const auto& shape : shapes) {
        for (size_t i = 0; i < 4; ++i) {
            const glm::vec2& p1 = shape->square[i];
            const glm::vec2& p2 = shape->square[(i + 1) % shape->square.size()];
            glm::vec2 normal = getEdgeNormal(p1, p2);

            auto proj1 = projectShapeOntoAxis(this->tr, normal);
            auto proj2 = projectShapeOntoAxis(obj, normal);

            if (!projectionsOverlap(proj1, proj2)) {
                return false;
            }

            double overlap = std::min(proj1.second - proj2.first, proj2.second - proj1.first);
            if (overlap < minOverlap) {
                minOverlap = overlap;
                minAxis = normal;
            }
        }
    }

    return true;
}

bool components::box_collider2d::detectCollision(components::transform* obj) {
    std::vector<components::transform*> shapes = { this->tr, obj };

    for (const auto& shape : shapes) {
        for (size_t i = 0; i < 4; ++i) {
            const glm::vec2& p1 = shape->square[i];
            const glm::vec2& p2 = shape->square[(i + 1) % shape->square.size()];
            glm::vec2 normal = getEdgeNormal(p1, p2);

            auto proj1 = projectShapeOntoAxis(this->tr, normal);
            auto proj2 = projectShapeOntoAxis(obj, normal);

            if (!projectionsOverlap(proj1, proj2)) {
                return false;
            }
        }
    }

    return true;
}

void components::box_collider2d::updateGameObj() {
    this->tr = gameObj->get_component<transform>();
}

void components::box_collider2d::update() {
    for (object* obj : sc->getObjects()) {
        if (gameObj == obj)
            continue;

        collision2d col(obj);

        if (detectCollision(obj->get_component<transform>())) {
            if (std::find_if(collision.begin(), collision.end(), [col](const collision2d& p) { if (col.gameObj == p.gameObj) return true; return false; }) != collision.end()) { continue; }
            collision.push_back(col);
        }
        else {
            collision.erase(std::remove_if(collision.begin(),
                collision.end(),
                [col](const collision2d& p)
                {
                    return p.gameObj == col.gameObj;
                }),
                collision.end());
        }
    }
}

std::vector<components::collision2d> components::box_collider2d::getAllCollisions() {
    return collision;
}

components::collision2d components::box_collider2d::getCollision(int index) {
    if (collision.size() > index) {
        return collision[index];
    }
    else {
        return zero_collision;
    }
}

std::string components::box_collider2d::toString() {
	return std::string("box_collider2d");
};