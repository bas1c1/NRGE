#include "../include/transform.h"

components::transform::~transform() {}
components::transform::transform() {}

components::transform::transform(api::camera* camera, int width, int height, glm::vec2 pos, ObjectType objType, glm::vec2 localScale, float rotationAngle) {
	this->objType = objType;
	switch (objType) {
	case ObjectType::BASE:
		this->pos = pos - glm::vec2(width / 2, height / 2);
		break;
	case ObjectType::CAMERA:
		this->pos = pos;
		break;
	}
	this->scale = localScale;
	this->rotationAngle = rotationAngle;
	this->width = width;
	this->height = height;
	this->camera = camera;
	this->square = std::vector<glm::vec2>(4);

	this->genSquare();
	scaleObj(scale);
}

void components::transform::update() {
	genSquare();
	scaleObj(scale);
	rotateObj(rotationAngle);
}

glm::vec2 components::transform::calculateCenter() {
	glm::vec2 A, B, C, D{};
	glm::vec2 intersection{};

	A = square[0];
	B = square[2];
	C = square[1];
	D = square[3];

	double denom = (B.x - A.x) * (D.y - C.y) - (B.y - A.y) * (D.x - C.x);

	double t = ((C.x - A.x) * (D.y - C.y) - (C.y - A.y) * (D.x - C.x)) / denom;
	double u = -((B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x)) / denom;
	if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
		intersection.x = A.x + t * (B.x - A.x);
		intersection.y = A.y + t * (B.y - A.y);
	}

	return glm::vec2(intersection);
}

void components::transform::scaleObj(glm::vec2 scale) {
	this->scale = scale;
	glm::vec2 center = calculateCenter();
	for (int i = 0; i < 4; i++) {
		float translatedX = square[i].x - center.x;
		float translatedY = square[i].y - center.y;

		float scaledX = translatedX * scale.x;
		float scaledY = translatedY * scale.y;

		square[i].x = scaledX + center.x;
		square[i].y = scaledY + center.y;
	}
}

glm::vec2 rotatePointAroundCenter(const glm::vec2& point, const glm::vec2& center, double angle) {
	double cos_a = cos(angle);
	double sin_a = sin(angle);
	glm::vec2 translated = { point.x - center.x, point.y - center.y };
	return {
		translated.x * cos_a - translated.y * sin_a + center.x,
		translated.x * sin_a + translated.y * cos_a + center.y
	};
}

void components::transform::rotateObj(float rotationAngle) {
	this->rotationAngle = rotationAngle;
	std::vector<glm::vec2> rotated;
	float angleRadians = this->rotationAngle * 3.1415926 / 180.0;
	glm::vec2 center = calculateCenter();
	for (const auto& point : square) {
		rotated.push_back(rotatePointAroundCenter(point, center, angleRadians));
	}
	this->square = rotated;
}

void components::transform::genSquare() {
	glm::vec2 npos = this->camera->project(pos);
	const glm::vec2 offset(npos.x + width, npos.y + height);

	square[0] = glm::vec2((npos.x), (npos.y));
	square[1] = glm::vec2((npos.x), (offset.y));
	square[2] = glm::vec2((offset.x), (offset.y));
	square[3] = glm::vec2((offset.x), (npos.y));
}

std::string components::transform::toString() {
	return std::string("transform");
}

void components::transform::goTo(glm::vec2 newPos) {
	switch (this->objType) {
	case ObjectType::BASE:
		this->pos = pos - glm::vec2(width / 2, height / 2);
		break;
	case ObjectType::CAMERA:
		this->pos = pos;
		break;
	default:
		this->pos = pos;
		break;
	}
}

glm::vec2 components::transform::getPos() { return pos; }
glm::vec2 components::transform::getScale() { return scale; }
float components::transform::getRotationAngle() { return rotationAngle; };
int components::transform::getWidth() { return width; }
int components::transform::getHeight() { return height; }
components::ObjectType components::transform::getObjType() { return objType; }

void components::transform::setPos(glm::vec2 pos) { this->pos = pos; }
void components::transform::setScale(glm::vec2 scale) { this->scale = scale; }
void components::transform::setRotationAngle(float rotationAngle) { this->rotationAngle = rotationAngle; }
void components::transform::setWidth(int width) { this->width = width; }
void components::transform::setHeight(int height) { this->height = height; }
void components::transform::setObjType(ObjectType objType) {
	this->objType = objType;
	switch (objType) {
	case ObjectType::BASE:
		this->pos = pos - glm::vec2(width / 2, height / 2);
		break;
	case ObjectType::CAMERA:
		this->pos = pos;
		break;
	}
}