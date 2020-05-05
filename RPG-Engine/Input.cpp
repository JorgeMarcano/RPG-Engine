#include "Input.h"

void Input::BeginNewFrame()
{
	//resets irrelevant keys every frame
	_pressedKeys.clear();
	_releasedKeys.clear();
}

void Input::KeyUpEvent(const SDL_Event& event)
{
	_releasedKeys[event.key.keysym.scancode] = true;
	_heldKeys[event.key.keysym.scancode] = false;
}

void Input::KeyDownEvent(const SDL_Event& event)
{
	_pressedKeys[event.key.keysym.scancode] = true;
	_heldKeys[event.key.keysym.scancode] = true;
}

bool Input::isKeyPressed(SDL_Scancode key)
{
	return _pressedKeys[key];
}

bool Input::isKeyReleased(SDL_Scancode key)
{
	return _releasedKeys[key];
}

bool Input::isKeyHeld(SDL_Scancode key)
{
	return _heldKeys[key];
}
