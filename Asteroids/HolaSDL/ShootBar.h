#pragma once
#include "Container.h"
#include "Observable.h"
#include "Observer.h"

class ShootBar : public Container, public Observer
{
public:
	ShootBar(SDLGame* game, double w);
	virtual ~ShootBar();
	virtual void receive(Message * msg);
private:
	double iniW_;
	double iniPosX_;
};

