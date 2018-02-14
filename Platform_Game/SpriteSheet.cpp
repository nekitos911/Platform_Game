#include "SpriteSheet.h"
#include "AnimDirectional.h"

SpriteSheet::SpriteSheet(TextureManager* textureManager) : textureManager_(textureManager), currentAnim_(nullptr),
spriteScale_(1.f,1.f), direction_(Direction::Right)
{}

SpriteSheet::~SpriteSheet()
{
	ReleaseSheet();
}

void SpriteSheet::ReleaseSheet()
{
	textureManager_->ReleaseResource(texture_);
	currentAnim_ = nullptr;
	while(animations_.begin() != animations_.end())
	{
		delete animations_.begin()->second;
		animations_.erase(animations_.begin());
	}
}

sf::Vector2i SpriteSheet::GetSpriteSize() const
{
	return spriteSize_;
}

sf::Vector2f SpriteSheet::GetSpritePos() const
{
	return sprite_.getPosition();
}

Direction SpriteSheet::GetDir() const
{
	return direction_;
}

BaseAnim* SpriteSheet::GetCurrentAnim()
{
	return currentAnim_;
}

void SpriteSheet::SetSpriteSize(const sf::Vector2i& size)
{
	spriteSize_ = size;
	sprite_.setOrigin(spriteSize_.x / 2, spriteSize_.y);
}

void SpriteSheet::SetSpritePos(const sf::Vector2f& pos)
{
	sprite_.setPosition(pos);
}

void SpriteSheet::SetDir(const Direction& dir)
{
	if(dir == direction_) return;
	direction_ = dir;
	currentAnim_->CropSprite();
}

void SpriteSheet::CropSprite(const sf::IntRect& rect)
{
	sprite_.setTextureRect(rect);
}

bool SpriteSheet::LoadSheet(const std::string& file)
{
	std::ifstream sheet;
	sheet.open(file);
	if(sheet.is_open())
	{
		ReleaseSheet();
		std::string line;
		while (std::getline(sheet,line))
		{
			if(line[0] == '|') continue;
			std::stringstream keystream(line);
			std::string type;
			keystream >> type;
			if(type == "Texture")
			{
				if(!texture_.empty())
				{
					std::cerr << "Dupliczte: " << file << std::endl;
					continue;
				}
				std::string texture;
				keystream >> texture;
				if(!textureManager_->RequireResource(texture))
				{
					std::cerr << "Could not set up texture: " << texture << std::endl;
				}
				texture_ = texture;
				sprite_.setTexture(*textureManager_->GetResource(texture_));
			}
			else if (type == "Size")
			{
				keystream >> spriteSize_.x >> spriteSize_.y;
				SetSpriteSize(spriteSize_);
			}
			else if(type == "Scale")
			{
				keystream >> spriteScale_.x >> spriteScale_.y;
				sprite_.setScale(spriteScale_);
			}
			else if(type == "AnimationType")
			{
				keystream >> animType_;
			}
			else if(type == "Animation")
			{
				std::string name;
				keystream >> name;
				if(animations_.find(name) != animations_.end())
				{
					std::cerr << "Duplicate anim (" << name << ") in: " << file << std::endl;
					continue;
				}
				BaseAnim *anim = nullptr;
				if(animType_ == "Directional")
				{
					anim = new AnimDirectional();
				} else
				{
					std::cerr << "Uknown Anim type: " << animType_ << std::endl;
					continue;
				}

				keystream >> *anim;
				anim->SetSpriteSheet(this);
				anim->SetName(name);
				anim->Reset();
				animations_.emplace(name, anim);

				if (currentAnim_) continue;
				currentAnim_ = anim;
				currentAnim_->Play();
			}
		}
		sheet.close();
		return true;
	}
	std::cerr << "! Failed loading spritesheet: " << file << std::endl;
	return false;
}

bool SpriteSheet::SetAnim(const std::string& name, const bool& isPlay, const bool& isLoop)
{
	auto itr = animations_.find(name);
	if (itr == animations_.end()) return false;
	if(itr->second == currentAnim_) return false;
	if (currentAnim_) currentAnim_->Stop();
	currentAnim_ = itr->second;
	currentAnim_->SetLooping(isLoop);
	if (isPlay) currentAnim_->Play();
	currentAnim_->CropSprite();
	return true;
}

void SpriteSheet::Update(const float& dt)
{
	currentAnim_->Update(dt);
}

void SpriteSheet::Draw(sf::RenderWindow* window)
{
	window->draw(sprite_);
}




