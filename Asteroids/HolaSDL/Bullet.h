#pragma once
#include "Container.h"

class Bullet : public Container {
public:
	Bullet(SDLGame* game);
	virtual ~Bullet();
	void setFighterId(int id) { fighterId_ = id; };
	int getFighterId() { return fighterId_; };
private:
	int fighterId_;
};
