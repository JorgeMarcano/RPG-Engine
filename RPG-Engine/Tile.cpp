#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(SDL_Texture* texture, Graphics* graphics, int w, int h, int tsX, int tsY, int x, int y)
{
	_tileset = texture;
	_graphics = graphics;

	_width = w;
	_height = h;

	_tsPosX = tsX;
	_tsPosY = tsY;

	_loc.x = x;
	_loc.y = y;

	_dstRect.x = x * w;
	_dstRect.y = y * h;
	_dstRect.w = w;
	_dstRect.h = h;

	_srcRect.x = tsX * w;
	_srcRect.y = tsY * h;
	_srcRect.w = w;
	_srcRect.h = h;
}

Tile::~Tile()
{
}

void Tile::Update(Uint32 dt, TileStruct offset)
{
	_dstRect.x = (_loc.x - offset.x) * _width;
	_dstRect.y = (_loc.y - offset.y) * _height;

	_srcRect.x = _tsPosX * _width;
	_srcRect.y = _tsPosY * _height;
}

void Tile::Draw()
{
	_graphics->DrawBlitOnWin(_tileset, &_srcRect, &_dstRect);
}
