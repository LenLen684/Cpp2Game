#pragma once
#include "Engine.h"

class Game
{
public:
	enum class eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver,
		GameWin
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateTitle(float dt);
	void UpdateLevelStart(float dt);
	void OnAddPoints(const nc::Event& e);
	void OnPlayerHit(const nc::Event& e);
	void LevelChange();

public:
	std::unique_ptr<nc::Engine> engine;
	std::unique_ptr<nc::Scene> scene;

private:
	eState state = eState::Title;
	float stateTimer = 0.0f;

	void (Game::*stateFn)(float) = nullptr;

	unsigned int score;
	unsigned int lives;
	int level;
	float pauseTimer;
	int enemies[5][3] = {
		{5, 2 ,2},
		{5, 4 ,3},
		{4, 4, 4},
		{3, 5, 5},
		{5, 5, 5}
	};

	std::shared_ptr<nc::Shape> shape = std::make_shared<nc::Shape>("PlayerDown.txt");
	std::shared_ptr<nc::Shape> enemy1 = std::make_shared<nc::Shape>("Enemy1.txt");
	std::shared_ptr<nc::Shape> enemy2 = std::make_shared<nc::Shape>("Enemy2.txt");
	std::shared_ptr<nc::Shape> enemy3 = std::make_shared<nc::Shape>("Enemy3.txt");
	

};