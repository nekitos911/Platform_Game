#include "AnimDirectional.h"
#include <SFML/Graphics/Rect.hpp>

void AnimDirectional::CropSprite()
{
	sf::IntRect rect(spriteSheet_->GetSpriteSize().x * currentFrame_,
		spriteSheet_->GetSpriteSize().y * (frameRow_ + static_cast<short>(spriteSheet_->GetDir())),
		spriteSheet_->GetSpriteSize().x, spriteSheet_->GetSpriteSize().y);
	spriteSheet_->CropSprite(rect);
}

void AnimDirectional::FrameStep()
{
	if (startFrame_ < endFrame_) ++currentFrame_;
	else
	{
		--currentFrame_;
	}

	if ((startFrame_ < endFrame_ && currentFrame_ > endFrame_) ||
		(startFrame_ > endFrame_ && currentFrame_ < endFrame_))
	{
		if(isLoop)
		{
			currentFrame_ = startFrame_;
			return;
		}
		currentFrame_ = endFrame_;
		Pause();
	}
}

void AnimDirectional::ReadIn(std::stringstream& stream)
{
	stream >> startFrame_ >> endFrame_ >> frameRow_ >>
		frameTime_ >> frameActionStart_ >> frameActionEnd_;
}


