#pragma once
#include "Vector2.h"

namespace nc {
	struct Transform {
		Vector2 position;
		float rotation;
		float scale;

		Transform() {};
		Transform(const Vector2& position, float rotation = 0, float scale = 1) : position{ position }, rotation{ rotation }, scale{ scale } {}
	};
	
}