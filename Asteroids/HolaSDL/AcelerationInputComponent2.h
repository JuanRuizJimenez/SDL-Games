#pragma once
#include "InputComponent.h"

class AcelerationInputComponent2 : public InputComponent
{
public:
	AcelerationInputComponent2(SDL_Keycode acelerate, SDL_Keycode desacelerate, double thrust,
		double maxVel, double reductionfactor);
	virtual ~AcelerationInputComponent2();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
private:
	SDL_Keycode acelerate_;
	SDL_Keycode desacelerate_;
	double thrust_;
	double maxVel_;
	double reductionFactor_;
};

