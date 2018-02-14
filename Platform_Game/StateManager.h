#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "BaseState.h"
#include "SharedContext.h"
#include <unordered_map>
#include <functional>

enum class StateType { Intro = 1, MainMenu, Game, Paused, GameOver, Credits};

using  StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager
{
public:
	StateManager(SharedContext *shared);
	~StateManager();

	void Update(const sf::Time &time);
	void Draw();

	void ProcessRequests();

	SharedContext *GetContext();
	bool HasState(const StateType &type);

	void SwitchTo(const StateType &type);
	void Remove(const StateType &type);

private:
	void CreateState(const StateType &type);
	void RemoveState(const StateType &type);

	template <class T>
	void RegisterState(const StateType &type)
	{
		stateFactory_[type] = [this]() -> BaseState*
		{
			return new T(this);
		};
	}

	StateFactory stateFactory_;
	StateContainer states_;
	TypeContainer toRemove_;
	SharedContext *shared_;
};

