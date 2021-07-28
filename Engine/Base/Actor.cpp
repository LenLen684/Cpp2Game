#include "Actor.h"
#include "Graphics/Shape.h"

namespace nc
{
	void Actor::Update(float dt)
	{

	}

	void Actor::Draw(Core::Graphics& graphics)
	{
		shape->Draw(graphics, transform);
	}

	float Actor::GetRadius()
	{
		return shape->radius * transform.scale;
	}
}