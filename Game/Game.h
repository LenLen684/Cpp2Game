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
		GameOver
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
	unsigned int level;

};