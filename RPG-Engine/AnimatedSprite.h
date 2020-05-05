#pragma once

#include "Sprite.h"
#include <string>
#include <map>

typedef struct Animation
{
	int startFrameX;
	int startFrameY;
	int frameCount;

	Uint32 timeToUpdate;

	std::string name;
} Animation;

class AnimatedSprite : public Sprite
{
private:
	
	int _currentFrame;
	Animation _currentAnimation;

	std::map<std::string, Animation> _animations;

	bool _isAnimating;
	bool _isOnce;
	Uint32 _timeElapsed;

public:

	AnimatedSprite();
	AnimatedSprite(Graphics* graph, const char* filename, int sourceX, int sourceY,
					int width, int height, float initX, float initY);

	virtual ~AnimatedSprite();

	void AddAnimation(Animation animation);
	void AddAnimation(std::string name, int startX, int startY, int frameCount, Uint32 time);

	void StartAnimation(std::string name, bool once = false, int startFrame = 0);

	void StopAnimation();

	void ResetAnimation();

	void Update(Uint32 dt);

	void Draw(int x, int y);
};

