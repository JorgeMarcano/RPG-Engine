#pragma once

#include <string>
#include <vector>
#include "Graphics.h"
#include "Input.h"
#include "Tile.h"
#include "AnimatedTile.h"
#include "tinyxml2.h"
#include "Player.h"

#include <sstream>
#include <algorithm>
#include <cmath>

typedef struct Exit {

	std::string mapName;
	int spawnX;
	int spawnY;

} Exit;

class Level
{
private:

	Graphics* _graphics;
	Input* _input;

	std::string _lvlName;

	float _spawnX;
	float _spawnY;

	//In tile count
	int _width;
	int _height;

	int _tileWidth;
	int _tileHeight;

	int _screenW;
	int _screenH;

	//SDL_Texture* _bgTexture;

	std::vector<Layer> _layers;
	std::vector<Tileset> _tileSets;
	std::vector<TileStruct> _collisionList;

	std::vector<TileStruct> _exitTiles;
	std::vector<Exit> _exitInfos;

	Player* _player;

	void LoadMap();

public:

	Level();
	Level(std::string lvlName, float playerX, float playerY, Graphics* graph, Input* input, int screenW, int screenH);

	~Level();

	void Update(Uint32 dt);
	void Draw();

	const int getTileW() const { return _tileWidth; };
	const int getTileH() const { return _tileHeight; };

	Level* checkExits(Uint32 dt);
};

