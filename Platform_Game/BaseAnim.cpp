#include "BaseAnim.h"



BaseAnim::BaseAnim() : currentFrame_(0), startFrame_(0),
frameRow_(0), frameTime_(0.f), elapsedTime_(0.f),frameActionStart_(-1),
frameActionEnd_(-1), isLoop(false),isPlaying(false)
{}


BaseAnim::~BaseAnim()
{
}

void BaseAnim::SetFrame(Frame frame)
{
	if((frame >= startFrame_ && frame <= endFrame_) ||
		(frame >= endFrame_ && frame <= startFrame_))
	{
		currentFrame_ = frame;
	}
}

bool BaseAnim::IsInAction()
{
	if (frameActionStart_ == -1 || frameActionEnd_ == -1) return true;
	return (currentFrame_ >= frameActionStart_ && currentFrame_ <= frameActionEnd_);
}

void BaseAnim::Reset()
{
	currentFrame_ = startFrame_;
	elapsedTime_ = 0.0f;
	CropSprite();
}

void BaseAnim::Update(const float& dt)
{
	if(!isPlaying) return;
	elapsedTime_ += dt;
	if (elapsedTime_ < frameTime_) return;
	FrameStep();
	CropSprite();
	elapsedTime_ = 0;
}

void BaseAnim::Play()
{
	isPlaying = true;
}

void BaseAnim::Pause()
{
	isPlaying = false;
}

void BaseAnim::Stop()
{
	isPlaying = false;
	Reset();
}

void BaseAnim::SetSpriteSheet(SpriteSheet *sheet)
{
	spriteSheet_ = sheet;
}

void BaseAnim::SetStartFrame(Frame frame)
{
	startFrame_ = frame;
}

void BaseAnim::SetEndFrame(Frame frame)
{
	endFrame_ = frame;
}

void BaseAnim::SetFrameRow(Frame frame)
{
	frameRow_ = frame;
}

void BaseAnim::SetFrameTime(float time)
{
	frameTime_ = time;
}

void BaseAnim::SetActionStart(Frame frame)
{
	frameActionStart_ = frame;
}

void BaseAnim::SetActionEnd(Frame frame)
{
	frameActionEnd_ = frame;
}

void BaseAnim::SetLooping(bool loop)
{
	isLoop = loop;
}

void BaseAnim::SetName(const std::string &name)
{
	name_ = name;
}

SpriteSheet* BaseAnim::GetSpriteSheet()
{
	return  spriteSheet_;
}

int BaseAnim::GetActionStart()
{
	return frameActionStart_;
}

int BaseAnim::GetActionEnd()
{
	return frameActionEnd_;
}

Frame BaseAnim::GetFrame()
{
	return currentFrame_;
}

Frame BaseAnim::GetStartFrame()
{
	return startFrame_;
}

Frame BaseAnim::GetEndFrame()
{
	return endFrame_;
}

float BaseAnim::GetFrameTime()
{
	return frameTime_;
}

float BaseAnim::GetElapsedTime()
{
	return elapsedTime_;
}

std::string BaseAnim::GetName()
{
	return name_;
}

bool BaseAnim::IsLooping()
{
	return isLoop;
}

bool BaseAnim::IsPlaying()
{
	return isPlaying;
}

Frame BaseAnim::GetFrameRow()
{
	return frameRow_;
}


















