#include "Graphics.h"

Graphics::Graphics()
{
	_window = NULL;
	_windowSurface = NULL;
	_renderer = NULL;
}

Graphics::~Graphics()
{
	Cleanup();
}

int Graphics::Setup(const char* title, int h, int w)
{
	_width = w;
	_height = h;

	//Initialize the window
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;

		return EXIT_FAILURE;
	}

	SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_ALLOW_HIGHDPI, &_window, &_renderer);
	//SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetWindowTitle(_window, title);

	if (_window == NULL)
	{
		std::cout << "SDL could not create a window! Error: " << SDL_GetError() << std::endl;

		return EXIT_FAILURE;
	}

	_windowSurface = SDL_GetWindowSurface(_window);

	return EXIT_SUCCESS;
}

SDL_Surface* Graphics::LoadBMP(const char* filename)
{
	if (!_spriteSheets.count(filename))
	{
		_spriteSheets[filename] = SDL_LoadBMP(filename);

		if (_spriteSheets[filename] == NULL)
		{
			std::cout << "SDL could not load " << filename << "! Error: " << SDL_GetError() << std::endl;
		}
	}

	return _spriteSheets[filename];
}

SDL_Surface* Graphics::LoadPNG(const char* filename)
{
	if (!_spriteSheets.count(filename))
	{
		_spriteSheets[filename] = IMG_Load(filename);

		if (_spriteSheets[filename] == NULL)
		{
			std::cout << "SDL could not load " << filename << "! Error: " << SDL_GetError() << std::endl;
		}
	}

	return _spriteSheets[filename];
}

SDL_Texture* Graphics::LoadTextureFromSurface(SDL_Surface* source)
{
	return SDL_CreateTextureFromSurface(_renderer, source);
}

SDL_Texture* Graphics::LoadTextureFromPNG(const char* filename)
{
	return LoadTextureFromSurface(LoadPNG(filename));
}

void Graphics::DrawBlitOnWin(SDL_Texture* src, const SDL_Rect* srcrect, SDL_Rect* dstrect)
{
	SDL_RenderCopy(_renderer, src, srcrect, dstrect);
}

/*void Graphics::SetFade(int alpha)
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, alpha);
	SDL_RenderFillRect(_renderer, NULL);
}*/

void Graphics::UpdateWindow()
{
	SDL_RenderPresent(_renderer);
}

void Graphics::ClearWindow()
{
	SDL_RenderClear(_renderer);
}

void Graphics::FreeSpriteSheets(SDL_Surface* bmpSurface)
{
	//SDL_FreeSurface(bmpSurface);
}

void Graphics::Cleanup()
{
	if (_windowSurface != NULL)
		SDL_FreeSurface(_windowSurface);

	if (_renderer != NULL)
		SDL_DestroyRenderer(_renderer);

	if (_window != NULL)
		SDL_DestroyWindow(_window);

	SDL_Quit();
}
