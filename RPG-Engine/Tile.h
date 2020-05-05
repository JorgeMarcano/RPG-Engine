#pragma once

#include <SDL.h>
#include "Graphics.h"

#include <vector>

typedef struct Tileset {

	SDL_Texture* texture;
	int firstGid;

	int tileCount;

} Tileset;

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
	int _locX;
	int _locY;

	SDL_Rect _dstRect;
	SDL_Rect _srcRect;

public:

	Tile();
	Tile(SDL_Texture* texture, Graphics* graphics, int w, int h, int tsX, int tsY, int x, int y);

	~Tile();

	void Update(Uint32 dt);
	void Draw();
};

typedef struct Layer {

	int width;
	int height;

	std::vector<Tile> tileList;

} Layer;

