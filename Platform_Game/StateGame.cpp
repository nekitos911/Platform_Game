#include "StateGame.h"



StateGame::StateGame(StateManager *stateManager) : BaseState(stateManager)
{
}


StateGame::~StateGame()
{
}

void StateGame::OnCreate()
{
	EventManager *evMgr = stateManager_->GetContext()->eventManager_;

	evMgr->AddCallback(StateType::Game, "Key_Esacape", &StateGame::MainMenu, this);
	evMgr->AddCallback(StateType::Game, "Key_P", &StateGame::Pause, this);
	//TODO add callbacks
	sf::Vector2f size = static_cast<sf::Vector2f>(stateManager_->GetContext()->window_->GetWindowSize());
	view_.setSize(size);
	view_.setCenter(size.x / 2.0f, size.y / 2.0f);
	view_.zoom(0.6f);
	stateManager_->GetContext()->window_->GetRenderWindow()->setView(view_);
	//TODO add map
}

void StateGame::OnDestroy()
{
	//TODO destroy
}

void StateGame::Activate()
{
}

void StateGame::Deactivate()
{
}

void StateGame::Update(const sf::Time& time)
{
	SharedContext *context = stateManager_->GetContext();

}

void StateGame::Draw()
{
}

void StateGame::Pause(EventDetails* details)
{
	stateManager_->SwitchTo(StateType::Paused);
}

void StateGame::MainMenu(EventDetails* details)
{
	stateManager_->SwitchTo(StateType::MainMenu);
}


