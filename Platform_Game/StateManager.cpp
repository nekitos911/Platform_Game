#include "StateManager.h"
#include "StateIntro.h"
#include "StateMainMenu.h"
#include "StateGame.h"
#include "StatePaused.h"
#include "StateGameOver.h"
#include <ppltasks.h>


StateManager::StateManager(SharedContext *shared) :  shared_(shared)
{
	RegisterState<StateIntro>(StateType::Intro);
	RegisterState<StateMainMenu>(StateType::MainMenu);
	RegisterState<StateGame>(StateType::Game);
	RegisterState<StatePaused>(StateType::Paused);
	RegisterState<StateGameOver>(StateType::GameOver);
}


StateManager::~StateManager()
{
	for(auto &itr : states_)
	{
		itr.second->OnDestroy();
		delete itr.second;
	}
}

void StateManager::Draw()
{
	if(states_.empty()) return;
	if(states_.back().second->IsTransparent() && states_.size() > 1)
	{
		auto itr = states_.end();
		while (itr != states_.begin())
		{
			if(itr != states_.end())
			{
				if(!itr->second->IsTransparent())
				{
					break;
				}
			}
			--itr;
		}
		for(; itr != states_.end(); ++itr)
		{
			shared_->window_->GetRenderWindow()->setView(itr->second->GetView());
			itr->second->Draw();
		} 
	}
	else
	{
		states_.back().second->Draw();
	}
}

void StateManager::Update(const sf::Time& time)
{
	if(states_.empty()) return;
	if(states_.back().second->IsTranscendent() && states_.size() > 1)
	{
		auto itr = states_.end();
		while (itr != states_.begin())
		{
			if(itr != states_.end())
			{
				if(!itr->second->IsTranscendent())
				{
					break;
				}
			}
			--itr;
		}
		for(; itr != states_.end(); ++itr)
		{
			itr->second->Update(time);
		}
	} else
	{
		states_.back().second->Update(time);
	}
}

SharedContext* StateManager::GetContext()
{
	return shared_;
}

bool StateManager::HasState(const StateType& type)
{
	for(auto itr = states_.begin(); itr != states_.end();++itr)
	{
		if(itr->first == type)
		{
			auto removed = std::find(toRemove_.begin(), toRemove_.end(), type);
			if(removed == toRemove_.end()) return true;
			return false;
		}
	}
	return false;
}

void StateManager::Remove(const StateType& type)
{
	toRemove_.push_back(type);
}

void StateManager::ProcessRequests()
{
	while (toRemove_.begin() != toRemove_.end())
	{
		RemoveState(*toRemove_.begin());
		toRemove_.erase(toRemove_.begin());
	}
}

void StateManager::SwitchTo(const StateType& type)
{
	shared_->eventManager_->SetCurrentState(type);
	for(auto itr = states_.begin();itr != states_.end();++itr)
	{
		if(itr->first == type)
		{
			states_.back().second->Deactivate();
			StateType tmpType = itr->first;
			BaseState *tmpState = itr->second;
			states_.erase(itr);
			states_.emplace_back(tmpType, tmpState);
			tmpState->Activate();
			shared_->window_->GetRenderWindow()->setView(tmpState->GetView());
			return;
		}
	}

	if (!states_.empty()) states_.back().second->Deactivate();
	CreateState(type);
	states_.back().second->Activate();
	shared_->window_->GetRenderWindow()->setView(states_.back().second->GetView());
}

void StateManager::CreateState(const StateType& type)
{
	auto newState = stateFactory_.find(type);
	if(newState == stateFactory_.end()) return;
	BaseState *state = newState->second();
	state->view_ = shared_->window_->GetRenderWindow()->getDefaultView();
	states_.emplace_back(type, state);
	state->OnCreate();
}

void StateManager::RemoveState(const StateType& type)
{
	for(auto itr = states_.begin();itr != states_.end();++itr)
	{
		if(itr->first == type)
		{
			itr->second->OnDestroy();
			delete itr->second;
			states_.erase(itr);
			return;
		}
	}
}




