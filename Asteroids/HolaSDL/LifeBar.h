#pragma once
#include "Container.h"
#include "Observable.h"
#include "Observer.h"

class LifeBar : public Container, public Observer
{
public:
	LifeBar(SDLGame* game, double w);
	virtual ~LifeBar();
	virtual void receive(Message * msg);
private:
	double iniW_;
	double iniPosX_;
};

