#pragma once
#include "BaseState.h"
#include "StateMainMenu.h"

class StateGame : public BaseState
{
public:
	StateGame(StateManager *stateManager);
	~StateGame();

	void OnCreate() override;
	void OnDestroy() override;

	void Activate() override;
	void Deactivate() override;

	void Update(const sf::Time& time) override;
	void Draw() override;

	void MainMenu(EventDetails *details);
	void Pause(EventDetails *details);
	void ToggleOverlay(EventDetails *details);

private:
	Map * gameMap_;
};

