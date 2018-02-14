#pragma once
#include "Window.h"
#include "TextureManager.h"

class Map;
struct SharedContext
{
	SharedContext() : window_(nullptr), eventManager_(nullptr),
	gameMap_(nullptr), textureManager_(nullptr)
	{}
	
	Window *window_;
	EventManager *eventManager_;
	Map *gameMap_;
	TextureManager* textureManager_;
};