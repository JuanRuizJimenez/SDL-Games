#pragma once
#include "Container.h"

class Asteroid : public Container {
public:
	Asteroid(SDLGame* game);
	virtual ~Asteroid();
	virtual void setGenerations(int generations) { generations_ = generations; };
	virtual int getGenerations() { return generations_; };
private:
	int generations_;
};