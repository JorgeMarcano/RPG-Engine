#include "Menu.h"

#include "Game.h"

void Menu::Action()
{
	Level* level;
	switch (_currItemIndx)
	{
	case 0:
		level = new Level("1", 6, 12, _graphics, _input, WIDTH, HEIGHT);
		_game->LoadLevel(level);
		break;
	case 1:
		level = new Level("2", 9, 9, _graphics, _input, WIDTH, HEIGHT);
		_game->LoadLevel(level);
		break;
	}

}

Menu::Menu()
{
}

Menu::Menu(Graphics* graph, Game* game, Input* input, std::string bgName, std::string arrowName, float arrowX, float arrowY) :
	_arrow(graph, arrowName.c_str(), 0, 0, arrowX, arrowY),
	_bg(graph, bgName.c_str(), 0, 0, 0, 0)
{
	_graphics = graph;
	_game = game;
	_input = input;

	_arrowX = arrowX;
	_arrowY = arrowY;

	_currItemIndx = 0;
}

Menu::~Menu()
{
}

void Menu::AddItem(MenuItem item)
{
	_items.push_back(item);
}

void Menu::AddItem(float posX, float posY)
{
	MenuItem item;
	item.posX = posX;
	item.posY = posY;

	_items.push_back(item);
}

void Menu::Update(Uint32 dt)
{
	if (_input->isKeyHeld(SDL_SCANCODE_RETURN))
	{
		Action();
	}

	else if (_input->isKeyPressed(SDL_SCANCODE_W) ||
		_input->isKeyPressed(SDL_SCANCODE_A))
	{
		_currItemIndx = (_currItemIndx - 1) % _items.size();

		if (_items.size() > 0)
		{
			_arrowX = _items[_currItemIndx].posX;
			_arrowY = _items[_currItemIndx].posY;
		}
	}
	else if (_input->isKeyPressed(SDL_SCANCODE_S) ||
		_input->isKeyPressed(SDL_SCANCODE_D))
	{
		_currItemIndx = (_currItemIndx + 1) % _items.size();

		if (_items.size())
		{
			_arrowX = _items[_currItemIndx].posX;
			_arrowY = _items[_currItemIndx].posY;
		}
	}
}

void Menu::Draw()
{
	_bg.DrawFull();

	_arrow.Draw(_arrowX, _arrowY);
}
