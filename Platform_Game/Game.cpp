#include "Game.h"



Game::Game() : window_(TITLE, WIDTH, HEIGHT), stateManager_(&context_)
{
	clock_.restart();
	srand(time(nullptr));

	context_.window_ = &window_;
	context_.eventManager_ = window_.GetEventManager();
	context_.textureManager_ = &textureManager_;

	stateManager_.SwitchTo(StateType::Intro);
}


Game::~Game()
{
}

void Game::Update()
{
	window_.Update();
	stateManager_.Update(elapsaedTime_);
}

void Game::Render()
{
	window_.BeginDraw();
	stateManager_.Draw();
	window_.EndDraw();
}

void Game::LateUpdate()
{
	RestartClock();
	stateManager_.ProcessRequests();
}

void Game::RestartClock()
{
	elapsaedTime_ = clock_.restart();
}

Window* Game::GetWindow()
{
	return &window_;
}

sf::Time Game::GetElapsedTime()
{
	return clock_.getElapsedTime();
}

