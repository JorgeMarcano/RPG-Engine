#pragma once

#include "string"
#include <SDL.h>
#include <map>
#include <vector>

typedef struct Frame
{
	SDL_Rect dstRect;

	int timeToUpdate;

} Frame;

typedef struct Animation
{
	std::vector<Frame> frames;

	int frameCount;

	std::string name;

} Animation;

class Animate
{
private:

	std::map<std::string, Animation> _animations;

	bool _isAnimating;
	bool _isOnce;
	Uint32 _timeElapsed;

protected:

	int _currentFrame;
	Animation _currentAnimation;

public:

	Animate();

	void AddAnimation(Animation animation);
	void AddAnimation(std::string name, int startX, int startY, int frameCount, Uint32 time);
	void AddAnimation(std::string name, std::vector<Frame> frames, int frameCount, Uint32 time);

	void StartAnimation(std::string name, bool once = false, int startFrame = 0);

	void StopAnimation();

	void ResetAnimation();

	void UpdateAnimation(Uint32 dt);

	virtual void SetSrcRectAnimated() = 0;
};

