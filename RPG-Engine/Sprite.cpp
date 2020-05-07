#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(Graphics* graph, const char* filename, int sourceX, int sourceY, int width, int height, float initX, float initY)
{
	_graphics = graph;
	_x = initX;
	_y = initY;
	_dx = 0;
	_dy = 0;

	_srcRect.x = sourceX;
	_srcRect.y = sourceY;
	_srcRect.w = width;
	_srcRect.h = height;

	_dstRect.w = width;
	_dstRect.h = height;

	_w = width;
	_h = height;

	_spriteSheet = _graphics->LoadTextureFromPNG(filename);
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
}

void Sprite::Draw(int x, int y)
{
	_dstRect.x = x;
	_dstRect.y = y;
	_graphics->DrawBlitOnWin(_spriteSheet, &_srcRect, &_dstRect);
}
