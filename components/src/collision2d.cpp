#include "../include/collision2d.h"

components::collision2d::~collision2d() {}
components::collision2d::collision2d() { this->gameObj = nullptr; }

components::collision2d::collision2d(object* gameObj) {
	this->gameObj = gameObj;
}