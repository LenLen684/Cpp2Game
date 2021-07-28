#include "Projectile.h"
#include "Engine.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	
	destroy = (lifetime <= 0);

	transform.position += nc::Vector2::Rotate(nc::Vector2::down, transform.rotation) * speed * dt;
	transform.position.x = nc::Wraparound(transform.position.x, 0.0f, 800.0f);
	transform.position.y = nc::Wraparound(transform.position.y, 0.0f, 600.0f);

	std::vector<nc::Color> colors = { nc::Color::white, nc::Color::red, nc::Color::green, nc::Color::blue, nc::Color::orange, nc::Color::yellow };
	scene->engine->Get<nc::ParticleSystem>()->Create(transform.position, 1.4, 0.5, colors[nc::RandomRangeInt(0, colors.size())], 50);
}