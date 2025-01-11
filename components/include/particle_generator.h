#pragma once

#include "../components.h"
#include "object.h"
#include <glm/glm.hpp>
#include "../../api/include/sprite_batching.h"
#include "../../api/include/scene.h"
#include "transform.h"

namespace components {
	struct particle_frame {
		glm::vec2 pos, velocity, size;
		float life;

		particle_frame() : life(0.0f) { pos = glm::vec2(0, 0); velocity = glm::vec2(0, 0); size = glm::vec2(0, 0); }
	};

	class particle_generator : public object::base_component {
	public:
		int amount;
		GLuint texture;

		glm::vec2 pos;
		glm::vec2 defaultSize;
		glm::vec2 defaultVelocity;
		float defaultLifetime;
		
		~particle_generator();
		particle_generator();
		particle_generator(api::scene* sc, int amount, glm::vec2 defaultSize, glm::vec2 defaultVelocity, float defaultLifetime, glm::vec2 pos);

		void updateGameObj() override;
		void update() override;
		std::string toString() override;
	private:
		std::vector<particle_frame> particles;
		sprite* sp;
		transform* tr;
		api::scene* sc;

		api::sprite_batching spb;
	};
}