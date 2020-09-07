#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "checkML.h"
#include "Bullet.h"
#include "Fighter.h"
#include "Observable.h"
#include "Observer.h"

class BulletsManager : public Observable, public Observer
{
public:
	BulletsManager();
	virtual ~BulletsManager();
	virtual std::vector<Bullet*>& getBullets() = 0;

private:
	virtual void shoot(Fighter* o, Vector2D p, Vector2D v) = 0;
};

