#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "BulletsManager.h"
#include "AsteroidsManager.h"
#include "FightersManager.h"
#include "Collisions.h"
#include "GameManager.h"
#include "GameManager.h"
#include "BonusManager.h"

class CollisionManager : public GameObject, public Observable
{
public:
	CollisionManager(SDLGame* game, BulletsManager* bulletsManager, 
		AsteroidsManager* astroidManager, FightersManager* fightersManager, 
		GameManager* gm, BonusManager* bonm, Observer* sm);
	virtual ~CollisionManager();
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time) {};
private:
	BulletsManager * bulletsManager_;
	AsteroidsManager* asteroidsManager_;
	FightersManager* fightersManager_;
	GameManager* gameManager_;
	BonusManager* bonusManager_;
};

