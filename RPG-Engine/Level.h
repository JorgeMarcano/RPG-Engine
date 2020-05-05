#pragma once

#include <string>
#include <vector>
#include "Graphics.h"
#include "Input.h"
#include "Tile.h"
#include "tinyxml2.h"

#include <sstream>
#include <algorithm>
#include <cmath>

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

	//SDL_Texture* _bgTexture;

	std::vector<Layer> _layers;
	std::vector<Tileset> _tileSets;

	void LoadMap();

public:

	Level();
	Level(std::string lvlName, float playerX, float playerY, Graphics* graph, Input* input);

	~Level();

	void Update(Uint32 dt);
	void Draw();
};

