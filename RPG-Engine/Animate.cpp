#include "Animate.h"

Animate::Animate()
{
	_currentFrame = 0;
	_isAnimating = false;
	_timeElapsed = 0;
	_isOnce = false;
}

void Animate::AddAnimation(Animation animation)
{
	_animations[animation.name] = animation;
}

void Animate::AddAnimation(std::string name, int startX, int startY, int frameCount, Uint32 time)
{
	Animation animation;
	animation.frameCount = frameCount;
	animation.name = name;
	std::vector<Frame> frames;
	Frame frame;
	frame.dstRect.x = startX;
	frame.dstRect.y = startY;
	frame.timeToUpdate = time;
	frames.push_back(frame);
	animation.frames = frames;

	AddAnimation(animation);
}

void Animate::AddAnimation(std::string name, std::vector<Frame> frames, int frameCount, Uint32 time)
{
	Animation animation;
	animation.frameCount = frameCount;
	animation.name = name;
	animation.frames = frames;

	AddAnimation(animation);
}

void Animate::StartAnimation(std::string name, bool once, int startFrame)
{
	if (_isAnimating && _currentAnimation.name == name)
		return;

	_isAnimating = true;
	_isOnce = once;

	_currentAnimation = _animations[name];

	_currentFrame = startFrame ? startFrame - 1 : _currentAnimation.frames.size() - 1;

	_timeElapsed = _currentAnimation.frames[_currentFrame].timeToUpdate + 1;
}

void Animate::StopAnimation()
{
	_isAnimating = false;
}

void Animate::ResetAnimation()
{
	if (!_isAnimating)
		return;

	_isAnimating = false;

	_currentFrame = 0;

	this->SetSrcRectAnimated();
}

void Animate::UpdateAnimation(Uint32 dt)
{
	if (!_isAnimating)
		return;

	_timeElapsed += dt;

	int size = _currentAnimation.frames.size();

	if (_timeElapsed >= _currentAnimation.frames[size == 1 ? 0 : _currentFrame].timeToUpdate)
	{
		_currentFrame++;

		if (_currentFrame >= _currentAnimation.frameCount)
		{
			_isAnimating = !_isOnce;
		}

		_currentFrame %= _currentAnimation.frameCount;

		this->SetSrcRectAnimated();

		_timeElapsed -= _currentAnimation.frames[size == 1 ? 0 : _currentFrame].timeToUpdate;
	}
}