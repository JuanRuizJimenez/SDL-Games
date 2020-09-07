#include "Bonus.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

Bonus::Bonus(SDLGame* game) : Container(game)
{
	srand(time(NULL));
	int num = rand() % 5;
	
	switch (num)
	{
	case 0:
		id_ = LIFE_BONUS;
		break;
	case 1:
		id_ = FEATHER_BONUS;
		break;
	case 2:
		id_ = BOMB_BONUS;
		break;
	case 3:
		id_ = TWHOMP_BONUS;
		break;
	case 4:
		id_ = BILL_BONUS;
		break;
	default:
		break;
	}
}

Bonus::~Bonus()
{
}
