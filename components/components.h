#pragma once

namespace components {
	class sprite;
	class sprite_renderer;
	class transform;
	class box_collider2d;
	class collision2d;
	class object;
	class rigidbody2d;

	enum class ObjectType {
		CAMERA,
		BASE,
		ANOTHER
	};
}