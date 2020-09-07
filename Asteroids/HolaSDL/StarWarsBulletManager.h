#pragma once
#include "BulletsManager.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "ImageRenderer.h"
#include "BasicMotionPhysics.h"
#include "checkML.h"
#include "Container.h"
#include "Bullet.h"
#include "messages.h"
#include "Fighter.h"

class StarWarsBulletManager : public GameObject, public BulletsManager
{
public:
	StarWarsBulletManager(SDLGame* game, Observer* sm);
	virtual ~StarWarsBulletManager();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, const SDL_Event& event) { };
	virtual std::vector<Bullet*>& getBullets() { return bullets; };
	virtual void receive(Message* msg);

private:
	Bullet* getBullet();
	void initBullets();
	virtual void shoot(Fighter* owner, Vector2D position, Vector2D velocity);
	void clear();

	std::vector<Bullet*> bullets;
	SDLGame* game_;
	int numOfBullets_;
	int maxSize_ = 25;
};

