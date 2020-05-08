#pragma once

#include "Tile.h"
#include "Animate.h"

class AnimatedTile : public Tile, public Animate
{
public:

	AnimatedTile();
	AnimatedTile(SDL_Texture* texture, Graphics* graphics, int w, int h, int tsX, int tsY, int x, int y);

	~AnimatedTile();

	void Update(Uint32 dt, TileStruct offset) override;
	void Draw();

	void SetSrcRectAnimated();
};

