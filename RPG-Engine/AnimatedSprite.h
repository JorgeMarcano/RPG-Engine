#pragma once

#include "Sprite.h"
#include "Animate.h"
#include <string>
#include <map>

class AnimatedSprite : public Sprite, public Animate
{
public:

	AnimatedSprite();
	AnimatedSprite(Graphics* graph, const char* filename, int sourceX, int sourceY,
					int width, int height, float initX, float initY);
	AnimatedSprite(Graphics* graph, const char* filename, int sourceX, int sourceY,
					float initX, float initY);

	virtual ~AnimatedSprite();

	void Update(Uint32 dt);

	void Draw(int x, int y);
	void DrawFull();

	void SetSrcRectAnimated();
};

