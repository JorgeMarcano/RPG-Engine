#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{
}

AnimatedSprite::AnimatedSprite(Graphics* graph, const char* filename, int sourceX, int sourceY, int width, int height, float initX, float initY) :
	Sprite(graph, filename, sourceX, sourceY, width, height, initX, initY)
{;
	_currentFrame = 0;
	_isAnimating = false;
	_timeElapsed = 0;
	_isOnce = false;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::AddAnimation(Animation animation)
{
	_animations[animation.name] = animation;
}

void AnimatedSprite::AddAnimation(std::string name, int startX, int startY, int frameCount, Uint32 time)
{
	Animation animation;
	animation.frameCount = frameCount;
	animation.name = name;
	animation.startFrameX = startX;
	animation.startFrameY = startY;
	animation.timeToUpdate = time;

	AddAnimation(animation);
}

void AnimatedSprite::StartAnimation(std::string name, bool once, int startFrame)
{
	if (_isAnimating && _currentAnimation.name == name)
		return;

	_isAnimating = true;
	_isOnce = once;

	_currentAnimation = _animations[name];

	_timeElapsed = _currentAnimation.timeToUpdate + 1;

	_currentFrame = startFrame - 1;
}

void AnimatedSprite::StopAnimation()
{
	_isAnimating = false;
}

void AnimatedSprite::ResetAnimation()
{
	if (!_isAnimating)
		return;

	_isAnimating = false;

	_currentFrame = 0;

	_srcRect.x = _currentAnimation.startFrameX + _srcRect.w * _currentFrame;
	_srcRect.y = _currentAnimation.startFrameY;
}

void AnimatedSprite::Update(Uint32 dt)
{
	Sprite::Update();

	if (!_isAnimating)
		return;

	_timeElapsed += dt;

	if (_timeElapsed >= _currentAnimation.timeToUpdate)
	{
		_currentFrame++;

		if (_currentFrame >= _currentAnimation.frameCount)
		{
			_isAnimating = !_isOnce;
		}

		_currentFrame %= _currentAnimation.frameCount;

		_srcRect.x = _currentAnimation.startFrameX + _srcRect.w * _currentFrame;
		_srcRect.y = _currentAnimation.startFrameY;

		_timeElapsed -= _currentAnimation.timeToUpdate;
	}
}

void AnimatedSprite::Draw(int x, int y)
{
	Sprite::Draw(x, y);
}
