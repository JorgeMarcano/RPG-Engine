#pragma once

#include "TileSprite.h"
#include "Input.h"
#include "Tile.h"

#define UP		SDL_SCANCODE_W
#define RIGHT	SDL_SCANCODE_D
#define DOWN	SDL_SCANCODE_S
#define LEFT	SDL_SCANCODE_A

#define RUN		SDL_SCANCODE_LSHIFT

#define SPEED		0.02f
#define RUNSPEED	0.04f
#define ACCEL		0.001f

class Player : public TileSprite
{
public:

	Player();
	Player(Graphics* graph, int initX, int initY, Input* input, int tileW, int tileH, int screenW, int screenH);

	~Player();

	void Update(Uint32 dt, std::vector<TileStruct> collisionList);

	void Draw();

	void Setup();

	void GetMovement(float* dx, float* dy);

	const void GetLoc(TileStruct* loc) const { loc->x = _loc.x; loc->y = _loc.y; };

	const void CalcOffset(TileStruct* offset) const;

private:

	Input* _input;

	bool _moving;

	const SDL_Scancode _CODES[4] = { UP, RIGHT, DOWN, LEFT };
	const std::string _ANIMS[4] = { "walk front" , "walk right", "walk down", "walk left" };

	const float TILESPERMILLI = 0.005f;
	//const float PIXELPERMILLI = 0.1f;

	int _screenW;
	int _screenH;
};

