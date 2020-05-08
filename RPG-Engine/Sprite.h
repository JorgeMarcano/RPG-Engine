#pragma once

#include "Graphics.h"

class Sprite
{
private:

	SDL_Texture* _spriteSheet;

	Graphics* _graphics;

protected:

	SDL_Rect _srcRect;
	SDL_Rect _dstRect;

	float _x;
	float _y;

	float _dx;
	float _dy;

	int _w;
	int _h;

public:

	Sprite();
	Sprite(Graphics* graph, const char* filename, int sourceX, int sourceY,
			int width, int height, float initX, float initY);
	Sprite(Graphics* graph, const char* filename, int sourceX, int sourceY,
			float initX, float initY);

	virtual ~Sprite();

	virtual void Update();

	void Draw(int x, int y);
	void DrawFull();
};

