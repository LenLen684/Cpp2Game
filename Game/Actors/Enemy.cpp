#include "Enemy.h"

#include "Player.h"
#include "Engine.h"
#include "Projectile.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);
	if (follows) {
		Player* player = scene->GetActor<Player>();
		if (player) {
			nc::Vector2 p1 = player->transform.position;
			nc::Vector2 p2 = transform.position;
			//nc::Vector2 direction = p1-p2;
			nc::Vector2 direction = {(p1.y - p2.y), -1*(p1.x - p2.x)};
			transform.rotation = nc::Lerp(transform.rotation, direction.Angle(), dt * speed);
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
		if (health >= 0) {
			destroy = true;
		}
		scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 30, 1, nc::Color::white, 50);
		
		nc::Event e;
		e.name = "AddPoints";
		scene->engine->Get<nc::EventSystem>()->Notify(e);
		
		scene->engine->Get<nc::AudioSystem>()->PlayAudio("explosion");
	}
}
