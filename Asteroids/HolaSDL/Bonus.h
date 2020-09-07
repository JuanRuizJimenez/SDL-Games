#pragma once
#include "Container.h"

enum type {
	LIFE_BONUS,
	FEATHER_BONUS,
	BOMB_BONUS,
	TWHOMP_BONUS,
	BILL_BONUS
};

class Bonus : public Container
{
public:
	Bonus(SDLGame* game);
	virtual ~Bonus();
	type id_;
};

