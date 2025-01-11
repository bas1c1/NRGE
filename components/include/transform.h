#pragma once

#include "../include/object.h"
#include "../../api/include/camera.h"
#include <glm/glm.hpp>

namespace components {
	class transform : public object::base_component {
	public:
		std::vector<glm::vec2> square;

		~transform();
		transform();
		transform(api::camera* camera, int width, int height, glm::vec2 pos = glm::vec2(0, 0), ObjectType objType = ObjectType::BASE, glm::vec2 localScale = glm::vec2(1, 1), float rotationAngle = 0);
		void update() override;
		std::string toString() override;
		void goTo(glm::vec2 newPos);
		glm::vec2 calculateCenter();

		glm::vec2 getPos();
		glm::vec2 getScale();
		float getRotationAngle();
		int getWidth();
		int getHeight();
		ObjectType getObjType();

		void setPos(glm::vec2 pos);
		void setScale(glm::vec2 scale);
		void setRotationAngle(float rotationAngle);
		void setWidth(int width);
		void setHeight(int height);
		void setObjType(ObjectType objType);
	private:
		int width;
		int height;
		glm::vec2 pos;
		glm::vec2 scale;
		float rotationAngle;
		api::camera *camera;

		void rotateObj(float rotationAngle);
		void scaleObj(glm::vec2 scale);
		void genSquare();
		ObjectType objType;
	};
}