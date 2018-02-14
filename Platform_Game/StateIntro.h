#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include  "StateManager.h"
#include "TextureManager.h"

class StateIntro : public BaseState
{
public:
	StateIntro(StateManager *stateMaanager);
	~StateIntro();

	void OnCreate() override;
	void OnDestroy() override;

	void Activate() override;
	void Deactivate() override;

	void Update(const sf::Time& time) override;
	void Draw() override;

	void Continue(EventDetails *details);

private:
	sf::Sprite introSprite_;
	sf::Font font_;
	sf::Text text_;
	float elapsedTime_;
};

