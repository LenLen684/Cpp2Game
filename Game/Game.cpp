#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"

void Game::Initialize()
{
	engine = std::make_unique<nc::Engine>();
	engine->Startup();
	scene = std::make_unique<nc::Scene>();
	scene->engine = engine.get();

	engine->Get<nc::AudioSystem>()->AddAudio("explosion", "Explosion.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("GameOver", "GameOver0.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("LevelStart", "LevelStart.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("PlayerHit", "PlayerHit.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("LongShot", "LongShoot.wav");
	engine->Get<nc::AudioSystem>()->AddAudio("TriShot", "TriangleShot.wav");

	engine->Get<nc::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<nc::EventSystem>()->Subscribe("PlayerHit", std::bind(&Game::OnPlayerHit, this, std::placeholders::_1));

}

void Game::Shutdown()
{
	scene->RemoveAllActors();
	engine->Shutdown();
}

void Game::Update(float dt)
{
	stateTimer += dt;
	
	switch (state)
	{
	case Game::eState::Title:
	{
		if (Core::Input::IsPressed(VK_SPACE)) {
			state = eState::StartGame;
		}
	}
		break;
	case Game::eState::StartGame:
	{
		score = 0;
		lives = 5;
		scene->RemoveAllActors();
		pauseTimer = 1.5f;
		state = eState::StartLevel;
		scene->AddActor(std::make_unique<Player>(nc::Transform(nc::Vector2(400.0f, 300.0f), 0.0f, 5.0f), shape, 200.0f));
	}
		break;
	case Game::eState::StartLevel:
	{
		if (level > 4) {
			state = eState::GameWin;
			break;
		}
		if (pauseTimer <= 0) {
			size_t j = 0;
			size_t k = enemies[level][0] + enemies[level][1] + enemies[level][2];
			for (size_t i = 0; i < k; i++)
			{
				if (i >= enemies[level][j] && j < 3) {
					j++;
				}
				switch (j)
				{
				case 0:
					scene->AddActor(std::make_unique<Enemy>(nc::Transform(nc::Vector2(nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)), nc::RandomRange(0.0f, nc::Tau), 5.0f), enemy1, 110.0f, false));
					break;
				case 1:
					scene->AddActor(std::make_unique<Enemy>(nc::Transform(nc::Vector2(nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)), nc::RandomRange(0.0f, nc::Tau), 4.0f), enemy2, 55.0f, true, 2));
					break;
				case 2:
					scene->AddActor(std::make_unique<Enemy>(nc::Transform(nc::Vector2(nc::RandomRange(0.0f, 800.0f), nc::RandomRange(0.0f, 600.0f)), nc::RandomRange(0.0f, nc::Tau), 6.0f), enemy3, 20.0f, true, 3, true));
					break;
				default:
					break;
				}
			}
			state = eState::Game;
		}
		else {
			pauseTimer -= dt;
		}
	}
		break;
	case Game::eState::Game:
		if (scene->GetActors<Enemy>().size() < 1) {
			level++;
			state = eState::StartLevel;
			pauseTimer = 1.5f;
		}
		break;
	case Game::eState::GameOver:
		if (Core::Input::IsPressed(VK_SPACE)) {
			state = eState::StartGame;
		}
		break;
	case Game::eState::GameWin:
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	switch (state)
	{
	case Game::eState::Title:
	{
		graphics.SetColor(nc::Color{ 0.3394639, 1.0, 0.7279196 });
		graphics.DrawString(330, 300 + (20 * std::sin(stateTimer * 3)), "Something with blasters");
		graphics.SetColor(nc::Color::cyan);
		graphics.DrawString(340, 360, "Press Space to Start");
		
	}
		break;
	case Game::eState::StartGame:

		break;
	case Game::eState::StartLevel:
		if (pauseTimer > 0) {
			graphics.SetColor(nc::Color::orange);
			char levelname = level + 1;
			char buf[12];
			snprintf(buf, 12, "Level %d", (level + 1));
			graphics.DrawString(365, 300, (buf));
		}
		break;
	case Game::eState::Game:

		break;
	case Game::eState::GameOver:
		graphics.SetColor(nc::Color::red);
		graphics.DrawString(365, 300, "Game Over");
		graphics.SetColor(nc::Color::cyan);
		graphics.DrawString(330, 360, "Press Space to Restart");
		break;
	case Game::eState::GameWin:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(365, 300, "You Win");
		graphics.SetColor(nc::Color::cyan);
		graphics.DrawString(330, 360, "Press Space to Restart");
		break;
	default:
		break;
	}
	graphics.SetColor(nc::Color{ 0.0f, 0.5f, 1.0f });
	graphics.DrawString(30, 20, std::to_string(score).c_str());
	graphics.SetColor(nc::Color{ 0.0f, 0.5f, 1.0f });
	graphics.DrawString(30, 30, std::to_string(lives).c_str());

	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE)) {
		stateFn = &Game::UpdateLevelStart;
		//state = eState::StartGame;
	}
}

void Game::UpdateLevelStart(float dt)
{
	std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>();
	shape->Load("PlayerDown.txt");

	std::shared_ptr<nc::Shape> enemy1 = std::make_shared<nc::Shape>();
	enemy1->Load("Enemy1.txt");

	std::vector<nc::Vector2> points = { { -5, -5 }, { 5, -5 }, { 0, 10 }, { -5, -5 } };
	std::shared_ptr<nc::Shape> shape2 = std::make_shared<nc::Shape>(points, nc::Color(0, 1, 0));

	scene->AddActor(std::make_unique<Player>(nc::Transform(nc::Vector2(400.0f, 300.0f), 0.0f, 6.0f), shape, 200.0f));
	for (size_t i = 0; i < 80; i++)
	{
		scene->AddActor(std::make_unique<Enemy>(nc::Transform(nc::Vector2(400.0f, 300.0f), nc::RandomRange(0.0f, nc::Tau), 4.0f), enemy1, 200.0f));
	}
}

void Game::OnAddPoints(const nc::Event& e)
{
	score += 100;
}

void Game::OnPlayerHit(const nc::Event& e)
{
	lives -= 1;
	if (lives == 0) {
		engine->Get<nc::AudioSystem>()->PlayAudio("GameOver");
		state = Game::eState::GameOver;
		scene->GetActor<Player>()->destroy = true;
		lives = 0;
	}
	else {
		engine->Get<nc::AudioSystem>()->PlayAudio("PlayerHit");
	}
}

void Game::LevelChange() {

}