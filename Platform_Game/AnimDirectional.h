#pragma once
#include "BaseAnim.h"
#include "SpriteSheet.h"

class AnimDirectional : public BaseAnim
{
protected:
	void FrameStep() override;
	void CropSprite() override;
	void ReadIn(std::stringstream& stream) override;
};

