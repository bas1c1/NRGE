#pragma once

#include "../components.h"
#include "object.h"
#include "collision2d.h"
#include "box_collider2d.h"
#include "../../api/include/camera.h"
#include "../../api/include/scene.h"

namespace components {
	struct AABB
	{
		glm::vec2 min;
		glm::vec2 max;
	};

	enum class rigidbodyType {
		DYNAMIC = 1,
		STATIC = 2,
		KINEMATIC = 3
	};

	class rigidbody2d : public object::base_component {
	public:
		rigidbodyType rbType;
		float impulse;
		float maxImpulse;
		int mass;
		float gravity;
		glm::vec2 velocity;

		~rigidbody2d();
		rigidbody2d();

		rigidbody2d(api::scene* sc, rigidbodyType rbType = rigidbodyType::DYNAMIC, int mass = 1, glm::vec2 velocity = glm::vec2(0, 0), float impulse = 0.0f, float maxImpulse = 10.f, float gravity = -9.81f);

		void updateGameObj() override;
		void update() override;
		std::string toString() override;

		void applyForce(glm::vec2 force);

	private:
		transform* tr;
		box_collider2d* bx;
		api::scene* sc;

		int resolveCollision(rigidbody2d* other);
	};
}