#pragma once

#include <map>
#include <SDL.h>

class Input
{
private:

	std::map<SDL_Scancode, char> _heldKeys;
	std::map<SDL_Scancode, char> _pressedKeys;
	std::map<SDL_Scancode, char> _releasedKeys;

public:

	void BeginNewFrame();

	void KeyUpEvent(const SDL_Event& event);
	void KeyDownEvent(const SDL_Event& event);

	bool isKeyPressed(SDL_Scancode key);
	bool isKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);
};

