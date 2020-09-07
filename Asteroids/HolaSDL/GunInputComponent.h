#pragma once
#include "InputComponent.h"
#include "Vector2D.h"
#include "StarWarsBulletManager.h"
#include "Observable.h"
#include "Observer.h"
#include <ctime>

class GunInputComponent : public InputComponent, public Observable
{
public:
	GunInputComponent(SDL_Keycode shoot, Observer* bm, Observer* shootbar, Uint8 shotsPerInterval, Uint32 timeInterval);
	virtual ~GunInputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
protected:
	SDL_Keycode shoot_;
	Observer* bm_;
	Uint8 shotsPerInterval_;
	Uint8 shotsRealized_;
	Uint32 timeInterval_;
	Uint32 iniTimeInterval_;
	clock_t t;
	float secondsPassed;
};

