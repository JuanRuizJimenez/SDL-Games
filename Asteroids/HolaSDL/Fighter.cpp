#include "Fighter.h"

Fighter::Fighter(SDLGame* game, int id) : Container(game), id_(id)
{
	lives_ = 5;
	maxLives_ = lives_;
}

Fighter::~Fighter()
{
}
