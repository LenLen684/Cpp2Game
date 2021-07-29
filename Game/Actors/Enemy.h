#pragma once
#include "Base/Actor.h"
#include "Projectile.h"

class Enemy : public nc::Actor
{
public:
	Enemy(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed) : nc::Actor{ transform, shape }, speed{speed}{}
	Enemy(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed, bool follows) : nc::Actor{ transform, shape }, speed{ speed }, follows{ follows }{}
	Enemy(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed, bool follows, int health) : nc::Actor{ transform, shape }, speed{ speed }, follows{ follows }, health{health}{}
	Enemy(const nc::Transform& transform, std::shared_ptr<nc::Shape> shape, float speed, bool follows, int health, bool shoots) : nc::Actor{ transform, shape }, speed{ speed }, follows{ follows }, health{ health }, shoots{shoots}{}

	void Update(float dt) override;
	void OnCollision(Actor* actor) override;
private:
	float speed{300};
	float fireTimer{ 0 };
	float fireRate{ 0.7 };
	bool follows{ false };
	bool shoots{ false };
	int health{ 1 };
	std::shared_ptr<nc::Shape> projectile{ std::make_shared<nc::Shape>("Projectile2.txt") };
};