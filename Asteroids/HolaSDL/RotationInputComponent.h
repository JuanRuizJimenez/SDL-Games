#pragma once
#include "InputComponent.h"
class RotationInputComponent :
	public InputComponent
{
public:
	RotationInputComponent(SDL_Keycode clockwise, SDL_Keycode counterclockwise, double degrees);
	virtual ~RotationInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
private:
	SDL_Keycode clockwise_;
	SDL_Keycode counterclockwise_;
	double degrees_;
};

