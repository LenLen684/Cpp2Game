#pragma once
#include "Base/Actor.h"

class Player : public nc::Actor
{
public:
	Player(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{ speed }{}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;

private:
	float fireTimer{ 0 };
	float fireRate{ 0.2f };
	float speed{ 300 };
	float iFrameTimer{ 0 };
	std::shared_ptr<nc::Shape> shape1 {std::make_shared<nc::Shape>("Projectile0.txt")};
};