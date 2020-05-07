#pragma once

#include "Tile.h"
#include "AnimatedSprite.h"

class TileSprite : public AnimatedSprite
{
protected:

	TileStruct _loc;

	int _tileW;
	int _tileH;

	int _direction;

public:

	TileSprite();
	TileSprite(Graphics* graph, const char* filename, int sourceX, int sourceY,
		int width, int height, float initX, float initY, int tileW, int tileH);

	virtual ~TileSprite();

	virtual void Update(Uint32 dt, std::vector<TileStruct> collisionList, TileStruct offset);

	void Draw();

	bool IsColliding(Uint32 dt, std::vector<TileStruct> collisionList);
	bool IsColliding(Uint32 dt, std::vector<TileStruct> collisionList, int* indx);
};

