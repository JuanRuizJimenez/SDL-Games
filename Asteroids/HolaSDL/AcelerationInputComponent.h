#pragma once
#include "InputComponent.h"
class AcelerationInputComponent :
	public InputComponent
{
public:
	AcelerationInputComponent(SDL_Keycode acelerate, SDL_Keycode desacelerate, double thrust, 
		double maxVel, double aFactor, double dFactor);
	virtual ~AcelerationInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
private:
	SDL_Keycode acelerate_;
	SDL_Keycode desacelerate_;
	double thrust_;
	double maxVel_;
	double aFactor_;
	double dFactor_;
};

