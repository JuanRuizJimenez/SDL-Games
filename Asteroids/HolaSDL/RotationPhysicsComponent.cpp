#include "RotationPhysicsComponent.h"
#include <stdlib.h>
#include <time.h>

RotationPhysicsComponent::RotationPhysicsComponent()
{
	degrees_ = rand() % 1 + 0.5;
	clockwise_ = rand() % 2;
	counterclockwise_ = !clockwise_;
}

RotationPhysicsComponent::~RotationPhysicsComponent()
{
}

void RotationPhysicsComponent::update(GameObject* o, Uint32 time) {
	Vector2D direction = o->getDirection();

	if (clockwise_) {
		direction.rotate(degrees_);
	}
	else if (counterclockwise_) {
		direction.rotate(-degrees_);
	}

	o->setDirection(direction);
}