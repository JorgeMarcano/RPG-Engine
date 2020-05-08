#pragma once

#include "AnimatedSprite.h"
#include <vector>

class Game;
class Input;

typedef struct MenuItem
{

	float posX;
	float posY;

} MenuItem;

class Menu
{
private:

	std::vector<MenuItem> _items;

	Game* _game;
	Input* _input;
	Graphics* _graphics;

	AnimatedSprite _bg;

	AnimatedSprite _arrow;

	float _arrowX;
	float _arrowY;

	int _currItemIndx;

	virtual void Action();

public:

	Menu();
	Menu(Graphics* graph, Game* game, Input* input, std::string bgName, std::string arrowName, float arrowX, float arrowY);
	~Menu();

	void AddItem(MenuItem item);
	void AddItem(float posX, float posY);

	virtual void Update(Uint32 dt);
	void Draw();

};

