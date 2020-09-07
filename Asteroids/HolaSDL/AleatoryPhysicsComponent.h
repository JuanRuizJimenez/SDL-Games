#pragma once
#include "PhysicsComponent.h"
#include <ctime>

class AleatoryPhysicsComponent : public PhysicsComponent
{
public:
	AleatoryPhysicsComponent();
	virtual ~AleatoryPhysicsComponent();
	virtual void update(GameObject* o, Uint32 time);
	void setMove(bool m) { move_ = m; };
	bool getMode() { return move_; };

	float secondsPassed_;
	Uint32 timeInterval_;
	Uint32 iniTimeInterval_;
	clock_t t;

private:
	bool move_ = false;
};

