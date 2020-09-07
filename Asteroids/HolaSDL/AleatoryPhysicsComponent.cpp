#include "AleatoryPhysicsComponent.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

AleatoryPhysicsComponent::AleatoryPhysicsComponent()
{
	srand(time(NULL));
	t = clock();
	timeInterval_ = 5;
	iniTimeInterval_ = timeInterval_;
}

AleatoryPhysicsComponent::~AleatoryPhysicsComponent()
{
}

void AleatoryPhysicsComponent::update(GameObject* o, Uint32 time) 
{
	secondsPassed_ = (clock() - t) / CLOCKS_PER_SEC;

	if (secondsPassed_ >= timeInterval_) {
		timeInterval_ += iniTimeInterval_;

		Vector2D position; double posX; double posY;
		posX = rand() % o->getGame()->getWindowWidth();
		posY = rand() % o->getGame()->getWindowHeight();
		position.setX(posX); position.setY(posY);
		o->setPosition(position);
	}
}