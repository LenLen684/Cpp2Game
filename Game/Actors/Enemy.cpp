#include "Enemy.h"

#include "Player.h"
#include "Engine.h"
#include "Projectile.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);
	Player* player = scene->GetActor<Player>();
	if (follows) {
		if (player) {
			nc::Vector2 p1 = player->transform.position;
			nc::Vector2 p2 = transform.position;
			nc::Vector2 direction = { (p1.y - p2.y), -1 * (p1.x - p2.x) };
			//nc::Vector2 direction = p1-p2;
			transform.rotation = nc::Lerp(transform.rotation, direction.Angle(), dt * speed);
		}
	}
	if (shoots) {
		if (player) {
			nc::Vector2 p1 = player->transform.position;
			nc::Vector2 p2 = transform.position;
			nc::Vector2 direction = { (p1.y - p2.y), -1 * (p1.x - p2.x) };
			nc::Vector2 forward = nc::Vector2::Rotate(nc::Vector2::right, transform.rotation);
			float angle = nc::Vector2::Angle(direction.Normalized(), forward);

			//fire
			fireTimer -= dt;
			if (fireTimer <= 0 && angle <= nc::QuarterPi) {
				scene->engine->Get<nc::AudioSystem>()->PlayAudio("TriShot");
				fireTimer = fireRate;
				nc::Transform t = transform;
				t.scale = 3.2f;
				std::unique_ptr<Projectile> p = std::make_unique<Projectile>(t, projectile, 400.0f);
				p->tag = "Enemy";
				p->lifetime = 0.5f;
				scene->AddActor(std::move(p));
			}
		}
	}

	transform.position += nc::Vector2::Rotate(nc::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = nc::Wraparound(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wraparound(transform.position.y, 0.0f, 600.0f);


}

void Enemy::OnCollision(Actor* actor)
{
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player") {
		actor->destroy = true;
		health--;
		if (health <= 0) {
			destroy = true;
		}
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 30, 1, nc::Color::white, 50);
		
		nc::Event e;
		e.name = "AddPoints";
		scene->engine->Get<nc::EventSystem>()->Notify(e);
		
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
	}
}
