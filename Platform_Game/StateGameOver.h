#pragma once
#include "BaseState.h"

class StateGameOver : public BaseState
{
public:
	StateGameOver(StateManager *stateManager);
	~StateGameOver();

	void OnCreate() override;
	void OnDestroy() override;

	void Activate() override;
	void Deactivate() override;

	void Update(const sf::Time& time) override;
	void Draw() override;
};

