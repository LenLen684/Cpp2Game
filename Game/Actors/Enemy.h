#pragma once
#include "Base/Actor.h"
#include "Projectile.h"

class Enemy : public nc::Actor
{
public:
	Enemy(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{speed}{}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;
private:
	float speed{300};
	bool follows{ false };
	int health{ 1 };
};