#include "CircularMotionPhysicsComponent.h"

CircularMotionPhysicsComponent::CircularMotionPhysicsComponent()
{
}

CircularMotionPhysicsComponent::~CircularMotionPhysicsComponent()
{
}

void CircularMotionPhysicsComponent::update(GameObject* o, Uint32 time) {

	Vector2D velocity = o->getVelocity();
	Vector2D position = o->getPosition() + velocity;

	double height = o->getHeight();

	if (position.getY() > o->getGame()->getWindowHeight()) 
	{
		Vector2D pos(o->getPosition().getX(), -o->getHeight());
		position = pos;
	}

	else if (position.getY() <= -o->getHeight()) 
	{
		Vector2D pos(o->getPosition().getX(), o->getGame()->getWindowHeight());
		position = pos;
	}

	else if (position.getX() > o->getGame()->getWindowWidth())
	{
		Vector2D pos(-o->getWidth(), o->getPosition().getY());
		position = pos;
	}

	else if (position.getX() <= -o->getWidth())
	{
		Vector2D pos(o->getGame()->getWindowWidth(), o->getPosition().getY());
		position = pos;
	}

	o->setPosition(position);
}