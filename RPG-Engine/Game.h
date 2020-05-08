#pragma once

#include "Graphics.h"
#include "Input.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include "Level.h"
#include "Menu.h"

#define WIDTH	640
#define HEIGHT	480

class Game
{
private:
	
	void GameLoop();

	void Draw();
	void Update(Uint32 dt);

	Graphics* _graphics;
	Input* _inputs;

	Level* _level;
	Level* _nextLvl;

	bool _inMenu;

	Menu* _menu;

public:

	Game();
	~Game();

	void LoadLevel(Level* lvl);
};

