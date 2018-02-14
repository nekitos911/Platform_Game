#pragma once
#include "BaseState.h"
#include  "StateManager.h"
#include "TextureManager.h"

class StateMainMenu : public BaseState
{
public:
	StateMainMenu(StateManager *stateManager);
	~StateMainMenu();

	void OnCreate() override;
	void OnDestroy() override;

	void Activate() override;
	void Deactivate() override;

	void Update(const sf::Time& time) override;
	void Draw() override;

	void OnClick(EventDetails *details);

private:

	sf::Vector2f buttonSize_;
	sf::Vector2f buttonPos_;
	unsigned buttonPadding_;

	sf::Font font_;
	sf::Text text_;
	sf::Sprite menuSprite_;

	sf::RectangleShape rects_[3];
	sf::Text lables_[3];

	int menuNumber_;
};

