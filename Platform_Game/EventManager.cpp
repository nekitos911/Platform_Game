#include "EventManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>


EventManager::EventManager() : currentState_(StateType(0)), hasFocus_(true)
{
	LoadBindings();
}

EventManager::~EventManager()
{
	for (auto &itr : bindings_)
		delete itr.second;
}

bool EventManager::AddBinding(Binding *binding)
{
	if (bindings_.find(binding->name_) != bindings_.end())
		return false;

	return bindings_.emplace(binding->name_, binding).second;
}

bool EventManager::RemoveBinding(std::string name)
{
	auto itr = bindings_.find(name);
	if (itr == bindings_.end()) return false;
	delete itr->second;
	bindings_.erase(itr);
	return true;
}


void EventManager::SetCurrentState(StateType state)
{
	currentState_ = state;
}

void EventManager::SetFocus(const bool& focus)
{
	hasFocus_ = focus;
}

void EventManager::HandleEvent(sf::Event& event)
{
	std::cout << event.key.code << std::endl;
	for(auto &itr1 : bindings_)
	{
		Binding *bind = itr1.second;
		for (auto &itr2 : bind->events_)
		{
			EventType sfmlEvent = (EventType)event.type;
			if(itr2.first != sfmlEvent) continue;
			if(sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				if(itr2.second.code_ == event.key.code)
				{
					if(bind->details_.keyCode_ != -1)
					{
						bind->details_.keyCode_ = itr2.second.code_;
					}
					++(bind->count_);
					break;
				}
			}
			else
			{
				if(sfmlEvent == EventType::WindowResized)
				{
					bind->details_.size_.x = event.size.width;
					bind->details_.size_.y = event.size.height;
				} else if (sfmlEvent == EventType::TextEntered)
				{
					bind->details_.textEntered_ = event.text.unicode;
				}
				++(bind->count_);
			}
		}
	}
}

void EventManager::Update()
{
	if (!hasFocus_) return;
	for (auto &itr1 : bindings_)
	{
		Binding *bind = itr1.second;
		for(auto &itr2 : bind->events_)
		{
			switch (itr2.first)
			{
			case (EventType::Keyboard) :
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(itr2.second.code_)))
				{
					if(bind->details_.keyCode_ != -1)
					{
						bind->details_.keyCode_ = itr2.second.code_;
					}
					++(bind->count_);
				}
				break;
			}
		}
		if(bind->events_.size() == bind->count_)
		{
			auto stateCallbacks = callbacks_.find(currentState_);
			auto otherCallbacks = callbacks_.find(StateType(0));

			if(stateCallbacks != callbacks_.end())
			{
				auto callItr = stateCallbacks->second.find(bind->name_);
				if(callItr != stateCallbacks->second.end())
				{
					callItr->second(&bind->details_);
				}
			}

			if(otherCallbacks != callbacks_.end())
			{
				auto callItr = otherCallbacks->second.find(bind->name_);
				if(callItr != otherCallbacks->second.end())
				{
					callItr->second(&bind->details_);
				}
			}
		}
		bind->count_ = 0;
		bind->details_.Clear();
	}
}

void EventManager::LoadBindings()
{
	std::string delimetr = ":";

	std::ifstream bindings;
	bindings.open("keys.cfg");
	if(!bindings.is_open())
	{
		std::cout << "Failer to open keys.cfg" << std::endl;
		return;
	}
	std::string line;
	while (std::getline(bindings,line))
	{
		std::stringstream keyStream(line);
		std::string callbackName;
		keyStream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keyStream.eof())
		{
			std::string keyVal;
			keyStream >> keyVal;
			int start = 0;
			int end = keyVal.find(delimetr);
			if(end == std::string::npos)
			{
				delete bind;
				bind = nullptr;
				break;
			}

			EventType type = EventType(std::stoi(keyVal.substr(start, end - start)));
			int code = std::stoi(keyVal.substr(end + delimetr.length(), keyVal.find(delimetr, end + delimetr.length())));

			EventInfo eventInfo;
			eventInfo.code_ = code;
			bind->BindEvent(type, eventInfo);
		}
		if (!AddBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();
}




