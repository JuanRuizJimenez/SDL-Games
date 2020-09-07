#pragma once
#include "GunInputComponent.h"
class MiniGunInputComponent : public GunInputComponent
{
public:
	MiniGunInputComponent(SDL_Keycode shoot, Observer* bm, Observer* shootbar, Uint8 shotsPerInterval, Uint32 timeInterval, Uint32 numShots);
	~MiniGunInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
protected:
	Uint32 numShots_;
};

