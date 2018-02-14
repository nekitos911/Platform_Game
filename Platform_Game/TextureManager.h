#pragma once
#include "ResourceManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
	TextureManager() : ResourceManager("textures.cfg")
	{}
	
	sf::Texture *Load(const std::string &path)
	{
		sf::Texture *texture = new sf::Texture();
		if(!texture->loadFromFile(path))
		{
			delete texture;
			texture = nullptr;
			std::cerr << "Faled to load texture: " << path << std::endl;
		}
		return texture;
	}
};

