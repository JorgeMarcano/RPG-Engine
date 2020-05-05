#include "Player.h"

Player::Player()
{
}

Player::Player(Graphics* graph, float initX, float initY, Input* input) :
	AnimatedSprite(graph, "content/character/bob.png", 0, 0, 48, 64, initX, initY)
{
	_input = input;

	Setup();

	_moving = false;
}

Player::~Player()
{
}

void Player::Update(Uint32 dt)
{
	if (_moving)
	{
		//check when to stop moving
		if (_input->isKeyReleased(_direction) || !_input->isKeyHeld(_direction))
		{
			_moving = false;
			ResetAnimation();

			_dy = 0;
			_dx = 0;
		}
	}
	else
	{
		//check to start moving
		for (int i = 0; i < 4; i++)
		{
			if (_input->isKeyHeld(_CODES[i])) 
			{
				_moving = true;

				StartAnimation(_ANIMS[i]);

				_direction = _CODES[i];

				_dy = ((i + 1) % 2) * PIXELPERMILLI;
				_dy = i < 2 ? -_dy : _dy;
				_dx = (i % 2) * PIXELPERMILLI;
				_dx = i > 2 ? -_dx : _dx;

				break;
			}
		}
	}

	_x += dt * _dx * (1 + _input->isKeyHeld(RUN));
	_y += dt * _dy * (1 + _input->isKeyHeld(RUN));

	AnimatedSprite::Update(dt);
}

void Player::Draw()
{
	AnimatedSprite::Draw(_x, _y);
}

void Player::Setup()
{
	AddAnimation(_ANIMS[3], 0, 64, 4, 300);
	AddAnimation(_ANIMS[1], 0, 128, 4, 300);
	AddAnimation(_ANIMS[2], 0, 0, 4, 300);
	AddAnimation(_ANIMS[0], 0, 192, 4, 300);
}

void Player::GetMovement(float* dx, float* dy)
{
	*dx = _dx;
	*dy = _dy;
}
