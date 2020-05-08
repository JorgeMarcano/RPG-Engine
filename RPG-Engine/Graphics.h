#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include <map>
#include <string>

class Graphics
{
private:

	SDL_Window* _window;
	SDL_Surface* _windowSurface;
	SDL_Renderer* _renderer;

	int _height;
	int _width;

	std::map<std::string, SDL_Surface*> _spriteSheets;

public:
	Graphics();
	~Graphics();

	int Setup(const char* title, int h, int w);

	SDL_Surface* LoadBMP(const char* filename);
	SDL_Surface* LoadPNG(const char* filename);

	SDL_Texture* LoadTextureFromSurface(SDL_Surface* source);
	SDL_Texture* LoadTextureFromPNG(const char* filename);

	void DrawBlitOnWin(SDL_Texture* src, const SDL_Rect* srcrect, SDL_Rect* dstrect);

	//void SetFade(int alpha);

	void UpdateWindow();
	void ClearWindow();

	void FreeSpriteSheets(SDL_Surface* bmpSurface);

	void Cleanup();
};

