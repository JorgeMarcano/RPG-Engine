#include "Game.h"

void Game::GameLoop()
{
	SDL_Event event;

	Uint32 lastUpdateTime = SDL_GetTicks();
	Uint32 currentTime;
	Uint32 currentFrameDuration;

	bool looping = true;
	while (looping)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				looping = false;
				break;
			case SDL_KEYDOWN:
				//make sure key isn't being held down
				if (event.key.repeat == 0)
					_inputs->KeyDownEvent(event);
				break;
			case SDL_KEYUP:
				_inputs->KeyUpEvent(event);
				break;
			}
		}

		if (_inputs->isKeyPressed(SDL_SCANCODE_ESCAPE))
			looping = false;

		currentTime = SDL_GetTicks();
		currentFrameDuration = currentTime - lastUpdateTime;
		if (currentFrameDuration > 16)
		{
			lastUpdateTime = currentTime;

			Update(currentFrameDuration);
			Draw();

			_inputs->BeginNewFrame();
		}
	}
}

void Game::Draw()
{
	_graphics->ClearWindow();

	if (_inMenu)
	{
		_menu->Draw();
	}
	else
	{
		_level->Draw();
	}

	_graphics->UpdateWindow();
}

void Game::Update(Uint32 dt)
{
	if (_inMenu)
	{
		_menu->Update(dt);
	}
	else
	{
		_level->Update(dt);

		_nextLvl = _level->checkExits(dt);
		if (_nextLvl != NULL)
		{
			_level = _nextLvl;
			_level->Update(dt);
			_nextLvl = NULL;
		}
	}
}

Game::Game()
{
	_graphics = new Graphics();

	_inputs = new Input();

	_nextLvl = NULL;

	_inMenu = true;

	if (_graphics->Setup("Game", HEIGHT, WIDTH) == EXIT_SUCCESS)
	{
		_menu = new Menu(_graphics, this, _inputs, "content/menu/bg.png", "content/menu/arrow.png", 100, 100);
		_menu->AddItem(100, 100);
		_menu->AddItem(100, 200);
		GameLoop();
	}
}

Game::~Game()
{
}

void Game::LoadLevel(Level* lvl)
{
	_level = lvl;
	_inMenu = false;
}
