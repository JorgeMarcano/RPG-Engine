#pragma once

#include "AnimatedSprite.h"
#include "Input.h"

#define UP		SDL_SCANCODE_W
#define RIGHT	SDL_SCANCODE_D
#define DOWN	SDL_SCANCODE_S
#define LEFT	SDL_SCANCODE_A

#define RUN		SDL_SCANCODE_LSHIFT

class Player : public AnimatedSprite
{
public:

	Player();
	Player(Graphics* graph, float initX, float initY, Input* input);

	~Player();

	void Update(Uint32 dt);

	void Draw();

	void Setup();

	void GetMovement(float* dx, float* dy);

private:

	Input* _input;

	SDL_Scancode _direction;

	bool _moving;

	const SDL_Scancode _CODES[4] = { UP, RIGHT, DOWN, LEFT };
	const std::string _ANIMS[4] = { "walk front" , "walk right", "walk down", "walk left" };

	const float TILESPERMILLI = 0.001f;
	const float PIXELPERMILLI = 0.1f;
};

