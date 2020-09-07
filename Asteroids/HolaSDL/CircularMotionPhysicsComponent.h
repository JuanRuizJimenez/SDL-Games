#pragma once
#include "PhysicsComponent.h"
class CircularMotionPhysicsComponent : public PhysicsComponent
{
public:
	CircularMotionPhysicsComponent();
	virtual ~CircularMotionPhysicsComponent();
	virtual void update(GameObject* o, Uint32 time);
};

