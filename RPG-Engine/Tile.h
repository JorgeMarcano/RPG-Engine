#pragma once

#include <SDL.h>
#include "Graphics.h"

#include <vector>

typedef struct Tileset {

	SDL_Texture* texture;
	int firstGid;

	int tileCount;

} Tileset;

typedef struct TileStruct {

	float x;
	float y;

} TileStruct;

class Tile
{
private:

	SDL_Texture* _tileset;

	Graphics* _graphics;

	int _width;
	int _height;

	//In tile count
	int _tsPosX;
	int _tsPosY;

	//In tile count
	TileStruct _loc;

	SDL_Rect _dstRect;
	SDL_Rect _srcRect;

public:

	Tile();
	Tile(SDL_Texture* texture, Graphics* graphics, int w, int h, int tsX, int tsY, int x, int y);

	~Tile();

	void Update(Uint32 dt, TileStruct offset);
	void Draw();
};

typedef struct Layer {

	int width;
	int height;

	std::vector<Tile> tileList;

} Layer;

