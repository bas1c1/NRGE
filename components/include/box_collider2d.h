#pragma once

#include "../include/object.h"
#include "../../api/include/scene.h"
#include "../include/collision2d.h"
#include "../include/transform.h"

namespace components {
	class box_collider2d : public object::base_component {
	public:
		~box_collider2d();
		box_collider2d();
		box_collider2d(api::scene *sc);

		bool detectCollisionOverlap(components::transform* obj, glm::vec2& minAxis, double& minOverlap);
		bool detectCollision(transform* obj);
		std::vector<collision2d> getAllCollisions();
		collision2d getCollision(int index = 0);

		void update() override;
		void updateGameObj() override;
		std::string toString() override;
	private:
		std::vector<collision2d> collision;
		api::scene* sc;
		transform* tr;
	};
}