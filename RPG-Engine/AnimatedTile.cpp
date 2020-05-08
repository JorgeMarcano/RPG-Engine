#include "AnimatedTile.h"

AnimatedTile::AnimatedTile()
{
}

AnimatedTile::AnimatedTile(SDL_Texture* texture, Graphics* graphics, int w, int h, int tsX, int tsY, int x, int y) : 
	Tile(texture, graphics, w, h, tsX, tsY, x, y),
	Animate()
{
}

AnimatedTile::~AnimatedTile()
{
}

void AnimatedTile::Update(Uint32 dt, TileStruct offset)
{
	Animate::UpdateAnimation(dt);
	Tile::Update(dt, offset);
}

void AnimatedTile::Draw()
{
	Tile::Draw();
}

void AnimatedTile::SetSrcRectAnimated()
{
	_tsPosX = _currentAnimation.frames[_currentFrame].dstRect.x;
	_tsPosY = _currentAnimation.frames[_currentFrame].dstRect.y;
}
