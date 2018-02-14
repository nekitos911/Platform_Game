#pragma once
#include "Window.h"
#include "Constants.h"
#include "StateManager.h"

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	Window *GetWindow();
	sf::Time GetElapsedTime();

private:
	void RestartClock();

	sf::Clock clock_;
	sf::Time elapsaedTime_;
	Window window_;
	StateManager stateManager_;
	SharedContext context_;
	TextureManager textureManager_;
};

