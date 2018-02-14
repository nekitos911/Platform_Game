#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.h"

class Window
{
public:
	Window();
	Window(const std::string &title, const unsigned width, const unsigned height);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsExit();
	bool IsFullScreen();
	bool IsFocused();

	void ToggleFullScreen(EventDetails *details);
	void Close(EventDetails *details = nullptr);

	sf::RenderWindow *GetRenderWindow();
	EventManager *GetEventManager();
	sf::Vector2u GetWindowSize();
	sf::FloatRect GetViewSpace();

private:
	void Setup(const std::string &title, const unsigned width, const unsigned height);
	void Create();

	sf::RenderWindow window_;
	EventManager eventManager_;
	sf::Vector2u windowSize_;
	std::string windowTitle_;
	bool isExit_;
	bool isFullScreen_;
	bool isFocused_;

};

