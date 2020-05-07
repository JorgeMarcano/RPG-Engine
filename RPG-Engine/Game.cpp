#include "Game.h"

void Game::GameLoop()
{
	_level = new Level("1", 6, 12, _graphics, _inputs, WIDTH, HEIGHT);

	SDL_Event event;

	Uint32 lastUpdateTime = SDL_GetTicks();
	Uint32 currentTime;
	Uint32 currentFrameDuration;

	bool looping = true;
	while (looping)
	{
		_inputs->BeginNewFrame();

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
		if (currentFrameDuration > 8)
		{
			lastUpdateTime = currentTime;

			Update(currentFrameDuration);
			Draw();
		}
	}
}

void Game::Draw()
{
	_graphics->ClearWindow();

	_level->Draw();

	_graphics->UpdateWindow();
}

void Game::Update(Uint32 dt)
{
	_level->Update(dt);

	Level* newLvl = _level->checkExits(dt);
	if (newLvl != NULL)
	{
		_level = newLvl;
		_level->Update(dt);
	}
}

Game::Game()
{
	_graphics = new Graphics();

	_inputs = new Input();

	if (_graphics->Setup("Game", HEIGHT, WIDTH) == EXIT_SUCCESS)
		GameLoop();
}

Game::~Game()
{
}
