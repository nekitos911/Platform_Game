#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <unordered_map>
#include <functional>

enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1
};

struct EventInfo
{
	EventInfo()
	{
		code_ = 0;
	}
	EventInfo(int event)
	{
		code_ = event;
	}
	union
	{
		int code_;
	};
};

struct EventDetails
{
	EventDetails(const std::string &bindName) : name_(bindName)
	{
		Clear();
	}

	void Clear()
	{
		size_ = sf::Vector2i(0, 0);
		textEntered_ = 0;
		keyCode_ = -1;
	}

	std::string name_;
	sf::Vector2i size_;
	sf::Uint32 textEntered_;
	int keyCode_;

};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding
{
	Binding(const std::string &name) : name_(name), details_(name), count_(0)
	{}
	
	void BindEvent(EventType type, EventInfo info = EventInfo())
	{
		events_.emplace_back(type, info);
	}

	Events events_;
	std::string name_;
	int count_;
	EventDetails details_;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager
{
public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding *binding);
	bool RemoveBinding(std::string name);

	void SetCurrentState(StateType state);
	void SetFocus(const bool &focus);

	template <class T>
	bool AddCallback(StateType state, const std::string &name, void(T::*func)(EventDetails*), T *instance)
	{
		auto itr = callbacks_.emplace(state, CallbackContainer()).first;
		auto tmp = std::bind(func, instance, std::placeholders::_1);
		return itr->second.emplace(name, tmp).second;
	}

	bool RemoveCallback(StateType state, const std::string &name)
	{
		auto itr1 = callbacks_.find(state);
		if (itr1 == callbacks_.end()) return false;
		auto itr2 = itr1->second.find(name);
		if (itr2 == itr1->second.end()) return false;
		itr1->second.erase(name);
		return true;
	}

	void HandleEvent(sf::Event &event);
	void Update();


private:
	void LoadBindings();

	StateType currentState_;
	Bindings bindings_;
	Callbacks callbacks_;
	bool hasFocus_;


};

