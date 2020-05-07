#include "TileSprite.h"

TileSprite::TileSprite()
{
}

TileSprite::TileSprite(Graphics* graph, const char* filename, int sourceX, int sourceY, int width, int height, float initX, float initY, int tileW, int tileH) :
	AnimatedSprite(graph, filename, sourceX, sourceY, width, height, initX * tileW, initY * tileH)
{
	_loc.x = initX;
	_loc.y = initY;

	_x = _loc.x * tileW;
	_y = _loc.y * tileH;

	_tileW = tileW;
	_tileH = tileH;

	_dstRect.w = (width / tileW) * tileW;
	//keeping ratio
	_dstRect.h = height * ((width / tileW) * tileW) / width;
	//not keeping ratio
	//_dstRect.h = (height / tileH) * tileH;
}

TileSprite::~TileSprite()
{
}

void TileSprite::Update(Uint32 dt, std::vector<TileStruct> collisionList, TileStruct offset)
{
	if (!IsColliding(dt, collisionList))
	{
		_loc.x += _dx * dt;
		_loc.y += _dy * dt;
	}

	_x = (_loc.x - offset.x) * _tileW;
	_y = (_loc.y + 1 - offset.y) * _tileH - _dstRect.h;

	AnimatedSprite::Update(dt);
}

void TileSprite::Draw()
{
	AnimatedSprite::Draw(_x, _y);
}

bool TileSprite::IsColliding(Uint32 dt, std::vector<TileStruct> collisionList)
{
	float newPosX = _loc.x + _dx * dt + (_dx > 0 ? 1 : 0);
	float newPosY = _loc.y + _dy * dt + (_dy > 0 ? 1 : 0);

	TileStruct temp;
	for (int i = 0; i < collisionList.size(); i++)
	{
		temp = collisionList[i];
		if (newPosX >= temp.x && newPosX < temp.x + 1)
			if (newPosY >= temp.y && newPosY < temp.y + 1)
				return true;
	}

	return false;
}

bool TileSprite::IsColliding(Uint32 dt, std::vector<TileStruct> collisionList, int* indx)
{
	float newPosX = _loc.x + _dx * dt + (_dx > 0 ? 1 : 0);
	float newPosY = _loc.y + _dy * dt + (_dy > 0 ? 1 : 0);

	TileStruct temp;
	for (int i = 0; i < collisionList.size(); i++)
	{
		temp = collisionList[i];
		if (newPosX >= temp.x && newPosX < temp.x + 1)
			if (newPosY >= temp.y && newPosY < temp.y + 1)
			{
				*indx = i;
				return true;
			}
	}

	return false;
}
