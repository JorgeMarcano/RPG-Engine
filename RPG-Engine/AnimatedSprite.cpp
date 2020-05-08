#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{
}

AnimatedSprite::AnimatedSprite(Graphics* graph, const char* filename, int sourceX, int sourceY, int width, int height, float initX, float initY) :
	Sprite(graph, filename, sourceX, sourceY, width, height, initX, initY),
	Animate()
{
}

AnimatedSprite::AnimatedSprite(Graphics* graph, const char* filename, int sourceX, int sourceY, float initX, float initY) :
	Sprite(graph, filename, sourceX, sourceY, initX, initY),
	Animate()
{
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Update(Uint32 dt)
{
	Sprite::Update();
	Animate::UpdateAnimation(dt);
}

void AnimatedSprite::Draw(int x, int y)
{
	Sprite::Draw(x, y);
}

void AnimatedSprite::DrawFull()
{
	Sprite::DrawFull();
}

void AnimatedSprite::SetSrcRectAnimated()
{
	_srcRect.x = _currentAnimation.frames[0].dstRect.x + _srcRect.w * _currentFrame;
	_srcRect.y = _currentAnimation.frames[0].dstRect.y;
}
