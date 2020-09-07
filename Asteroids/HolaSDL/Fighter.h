#pragma once
#include "Container.h"
class Fighter : public Container
{
public:
	Fighter(SDLGame* game, int id);
	virtual ~Fighter();
	int getId() { return id_; };
	void setId(int id) { id_ = id; };
	int getLives() { return lives_; };
	void setLives(int l) { lives_ = l; };
	int getMaxLives() { return maxLives_; };
	
private:
	int id_;
	int lives_;
	int maxLives_;
};

