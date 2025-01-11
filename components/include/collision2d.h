#pragma once

#include "../components.h"

namespace components {
	class collision2d {
	public:
		object* gameObj;

		~collision2d();
		collision2d();
		collision2d(object* gameObj);
	private:

	};
	static collision2d zero_collision = components::collision2d::collision2d();
}