#include "Player.h"

Player::Player()
{
}

Player::Player(Graphics* graph, int initX, int initY, Input* input, int tileW, int tileH, int screenW, int screenH) :
	TileSprite(graph, "content/character/bob.png", 0, 0, 48, 64, initX, initY, tileW, tileH)
{
	_input = input;

	Setup();

	_moving = false;

	_screenH = screenH;
	_screenW = screenW;
}

Player::~Player()
{
}

void Player::Update(Uint32 dt, std::vector<TileStruct> collisionList)
{
	if (_moving)
	{
		//check when to stop moving
		if (_input->isKeyReleased(_CODES[_direction]) || !_input->isKeyHeld(_CODES[_direction]))
		{
			if ((int)(_loc.x + _dx * dt) != (int)_loc.x || (int)(_loc.y + _dy * dt) != (int)_loc.y || IsColliding(dt, collisionList))
			{
				_moving = false;
				ResetAnimation();

				if (_dx > 0 || _dy > 0)
				{
					_loc.x += _dx * dt;
					_loc.y += _dy * dt;
				}

				_loc.x = (int)_loc.x;
				_loc.y = (int)_loc.y;

				_dy = 0;
				_dx = 0;
			}
		}
	}
	else
	{
		//check to start moving
		for (int i = 0; i < 4; i++)
		{
			if (_input->isKeyHeld(_CODES[i])) 
			{
				_dy = ((i + 1) % 2) * TILESPERMILLI;
				_dy = i < 2 ? -_dy : _dy;
				_dx = (i % 2) * TILESPERMILLI;
				_dx = i > 2 ? -_dx : _dx;

				StartAnimation(_ANIMS[i]);

				_direction = i;

				_moving = true;

				break;
			}
		}
	}

	//_maxVel = _input->isKeyHeld(RUN) ? RUNSPEED : SPEED;

	TileStruct offset;
	CalcOffset(&offset);

	TileSprite::Update(dt, collisionList, offset);
}

void Player::Draw()
{
	TileSprite::Draw();
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

const void Player::CalcOffset(TileStruct* offset) const
{
	GetLoc(offset);

	offset->x -= (0.5 * _screenW / _tileW) + 0.5;
	offset->y -= (0.5 * _screenH / _tileH) + 0.5;
}
