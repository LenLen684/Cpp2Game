#include "Player.h"
#include "Projectile.h"
#include "Engine.h"
#include "Enemy.h"

#include <memory>

void Player::Update(float dt)
{
	Actor::Update(dt);

	float thrust = 0;
	if (Core::Input::IsPressed('A')) transform.rotation -= 5 * dt;
	if (Core::Input::IsPressed('D')) transform.rotation += 5 * dt;
	if (Core::Input::IsPressed('W')) thrust = speed;
	if (Core::Input::IsPressed('S')) thrust = -speed;

	transform.position += nc::Vector2::Rotate(nc::Vector2::down, transform.rotation) * thrust * dt;
	transform.position.x = nc::Wraparound(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wraparound(transform.position.y, 0.0f, 600.0f);

	//fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE)) {
		fireTimer = fireRate;
		nc::Transform t = transform;
		t.scale = 4;
		std::unique_ptr<Projectile> p = std::make_unique<Projectile>(t, shape1, 200.0f);
		p->tag = "Player";
		scene->AddActor(std::move(p));
	}

	scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 3, 2, nc::Color::white, 50);
	iFrameTimer -= dt;
}

void Player::OnCollision(Actor* actor)
{
	if (iFrameTimer <= 0) {
		if (dynamic_cast<Enemy*>(actor)) {
			scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 30, 1, nc::Color{ 0.3, 0.5, 0 }, 50);

			nc::Event e;
			e.name = "PlayerHit";
			scene->engine->Get<nc::EventSystem>()->Notify(e);
			iFrameTimer = 1.2;
		}
		else if ((dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy")) {
			actor->destroy = true;

			nc::Event e;
			e.name = "PlayerHit";
			scene->engine->Get<nc::EventSystem>()->Notify(e);
			iFrameTimer = 2;
		}
	}
}

