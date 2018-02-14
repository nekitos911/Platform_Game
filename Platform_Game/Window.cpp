#include "Window.h"
#include <iostream>

Window::Window() : Window("Untitled", 640, 480)
{}

Window::Window(const std::string& title, const unsigned width, const unsigned height)
{
	Setup(title, width, height);
}

Window::~Window()
{
	window_.close();
}


void Window::Setup(const std::string& title, const unsigned width, const unsigned height)
{
	windowTitle_ = title;
	windowSize_ = sf::Vector2u(width, height);
	isFullScreen_ = false;
	isExit_ = false;
	isFocused_ = true;

	eventManager_.AddCallback(StateType(0), "Fullscreen_toggle", &Window::ToggleFullScreen, this);
	eventManager_.AddCallback(StateType(0), "Window_close", &Window::Close, this);

	Create();
}

void Window::Create()
{
	auto style = (isFullScreen_ ? sf::Style::Fullscreen : sf::Style::Default);
	window_.create(sf::VideoMode(windowSize_.x, windowSize_.y), windowTitle_, style);
}

void Window::Update()
{
	sf::Event event;

	while (window_.pollEvent(event)) 
	{
		if(event.type == sf::Event::LostFocus)
		{
			isFocused_ = false;
			eventManager_.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			isFocused_ = true;
			eventManager_.SetFocus(true);
		}
		eventManager_.HandleEvent(event);
	}
	eventManager_.Update();
	if(event.type == sf::Event::KeyPressed)
		std::cout << event.key.code << std::endl;
}

void Window::ToggleFullScreen(EventDetails* details)
{
	isFullScreen_ = !isFullScreen_;
	window_.close();
	Create();
}



bool Window::IsExit()
{
	return isExit_;
}

bool Window::IsFullScreen()
{
	return isFullScreen_;
}

bool Window::IsFocused()
{
	return isFocused_;
}

void Window::BeginDraw()
{
	window_.clear();
}

void Window::EndDraw()
{
	window_.display();
}

sf::RenderWindow *Window::GetRenderWindow()
{
	return &window_;
}

sf::Vector2u Window::GetWindowSize()
{
	return windowSize_;
}

void Window::Close(EventDetails* details)
{
	isExit_ = true;
}

EventManager *Window::GetEventManager()
{
	return &eventManager_;
}

sf::FloatRect Window::GetViewSpace()
{
	sf::Vector2f viewCenter(window_.getView().getCenter());
	sf::Vector2f viewSize(window_.getView().getSize());
	sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
	sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
	return viewSpace;
}









