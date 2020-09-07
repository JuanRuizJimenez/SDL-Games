#pragma once
#include "PhysicsComponent.h"

class RotationPhysicsComponent : public PhysicsComponent
{
public:
	RotationPhysicsComponent();
	virtual ~RotationPhysicsComponent();
	virtual void update(GameObject* o, Uint32 time);
private:
	bool clockwise_;
	bool counterclockwise_;
	double degrees_;
};

