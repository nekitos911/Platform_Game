#pragma once
#include <string>

class SpriteSheet;

using Frame = unsigned;

class BaseAnim
{
	friend class SpriteSheet;
public:
	BaseAnim();
	virtual ~BaseAnim();

	void SetSpriteSheet(SpriteSheet *sheet);
	void SetFrame(Frame frame);
	void SetStartFrame(Frame frame);
	void SetEndFrame(Frame frame);
	void SetFrameRow(Frame frame);
	void SetActionStart(Frame frame);
	void SetActionEnd(Frame frame);
	void SetFrameTime(float time);
	void SetLooping(bool loop);
	void SetName(const std::string &name);

	SpriteSheet* GetSpriteSheet();
	Frame GetFrame();
	Frame GetStartFrame();
	Frame GetEndFrame();
	Frame GetFrameRow();
	int GetActionStart();
	int GetActionEnd();
	float GetFrameTime();
	float GetElapsedTime();
	bool IsLooping();
	bool IsPlaying();
	bool IsInAction();
	std::string GetName();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	virtual void Update(const float &dt);

	friend std::stringstream &operator >>(std::stringstream &stream, BaseAnim &anim)
	{
		anim.ReadIn(stream);
		return stream;
	}

protected:
	virtual void FrameStep() = 0;
	virtual void CropSprite() = 0;
	virtual void ReadIn(std::stringstream &stream) = 0;

	Frame currentFrame_;
	Frame startFrame_;
	Frame endFrame_;
	Frame frameRow_;
	int frameActionStart_;
	int frameActionEnd_;
	float frameTime_;
	float elapsedTime_;
	bool isLoop;
	bool isPlaying;

	std::string name_;

	SpriteSheet* spriteSheet_;
};

