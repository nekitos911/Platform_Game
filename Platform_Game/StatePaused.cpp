#include "StatePaused.h"



StatePaused::StatePaused(StateManager* stateManager) : BaseState(stateManager)
{
	
}


StatePaused::~StatePaused()
{
}

void StatePaused::OnCreate()
{
	SetTransparent(true);
	font_.loadFromFile("Test.ttf");
	text_.setFont(font_);
	text_.setString(sf::String("PAUSED"));
	text_.setCharacterSize(20);
	text_.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = stateManager_->GetContext()->window_->GetRenderWindow()->getSize();

	sf::FloatRect textRect = text_.getLocalBounds();
	text_.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text_.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	rect_.setSize(sf::Vector2f(windowSize));
	rect_.setPosition(0, 0);
	rect_.setFillColor(sf::Color(0, 0, 0, 150));

	EventManager *evMgr = stateManager_->GetContext()->eventManager_;
	evMgr->AddCallback(StateType::Paused, "Key_P", &StatePaused::Unpause, this);
}

void StatePaused::OnDestroy()
{
	EventManager *evMgr = stateManager_->GetContext()->eventManager_;
	evMgr->RemoveCallback(StateType::Paused, "Key_P");
}

void StatePaused::Activate()
{
}

void StatePaused::Deactivate()
{
}

void StatePaused::Update(const sf::Time & time)
{
}

void StatePaused::Draw()
{
	sf::RenderWindow *window = stateManager_->GetContext()->window_->GetRenderWindow();
	window->draw(rect_);
	window->draw(text_);
}

void StatePaused::Unpause(EventDetails* details)
{
	stateManager_->SwitchTo(StateType::Game);
}

