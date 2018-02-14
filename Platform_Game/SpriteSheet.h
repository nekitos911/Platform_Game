#pragma once
#include <unordered_map>
#include "BaseAnim.h"
#include "TextureManager.h"
#include "Directions.h"

using Animations = std::unordered_map<std::string, BaseAnim*>;

class SpriteSheet
{
public:
	SpriteSheet(TextureManager *textureManager);
	~SpriteSheet();

	void CropSprite(const sf::IntRect &rect);
	sf::Vector2i GetSpriteSize() const;
	sf::Vector2f GetSpritePos() const;
	void SetSpriteSize(const sf::Vector2i &size);
	void SetSpritePos(const sf::Vector2f &pos);

	void SetDir(const Direction &dir);
	Direction GetDir() const;

	bool LoadSheet(const std::string &file);
	void ReleaseSheet();

	BaseAnim *GetCurrentAnim();
	bool SetAnim(const std::string &name,
		const bool &isPlay = false, const bool &isLoop = false);

	void Update(const float &dt);
	void Draw(sf::RenderWindow *window);

private:
	std::string texture_;
	sf::Sprite sprite_;
	sf::Vector2i spriteSize_;
	sf::Vector2f spriteScale_;
	Direction direction_;

	std::string animType_;
	Animations animations_;
	BaseAnim *currentAnim_;

	TextureManager *textureManager_;


};
