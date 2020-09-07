#include "StarWarsBulletManager.h"

StarWarsBulletManager::StarWarsBulletManager(SDLGame* game, Observer* sm) : GameObject(game)
{
	registerObserver(sm);
	game_ = game;
	numOfBullets_ = 5;
}	

StarWarsBulletManager::~StarWarsBulletManager()
{
	clear();
}

void StarWarsBulletManager::shoot(Fighter* o, Vector2D p, Vector2D v)
{
	Bullet* bullet = getBullet();
	bullet->setActive(true);
	bullet->setWidth(7); bullet->setHeight(30);
	bullet->setPosition(p);
	bullet->setVelocity(v);
	v.normalize();
	bullet->setDirection(v);

	MessageId id = BULLET_CREATED;
	Message m(id);
	send(&m);
}

void StarWarsBulletManager::update(Uint32 time)
{
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->isActive())
			bullets[i]->update(time);
	}

	std::vector<Bullet*>::iterator bulletIT = bullets.begin();
	int i = 0; bool erased = false;
	while (i < bullets.size() && !erased) {
		GameObject* o = bullets[i];
		Vector2D velocity = o->getVelocity();
		Vector2D position = o->getPosition() + velocity;

		if (position.getY() > o->getGame()->getWindowHeight())
		{
			bullets[i]->setActive(false);

			if (bullets.size() > maxSize_) {
				if (bullets[i] != nullptr && !bullets[i]->isActive()) {
					delete bullets[i];
					bullets[i] = nullptr;
					bullets.erase(bulletIT);
					erased = true;
				}
			}
		}

		else if (position.getY() <= -o->getHeight())
		{
			bullets[i]->setActive(false);

			if (bullets.size() > maxSize_) {
				if (bullets[i] != nullptr && !bullets[i]->isActive()) {
					delete bullets[i];
					bullets[i] = nullptr;
					bullets.erase(bulletIT);
					erased = true;
				}
			}
		}

		else if (position.getX() > o->getGame()->getWindowWidth())
		{
			bullets[i]->setActive(false);

			if (bullets.size() > maxSize_) {
				if (bullets[i] != nullptr && !bullets[i]->isActive()) {
					delete bullets[i];
					bullets[i] = nullptr;
					bullets.erase(bulletIT);
					erased = true;
				}
			}
		}

		else if (position.getX() <= -o->getWidth())
		{
			bullets[i]->setActive(false);

			if (bullets.size() > maxSize_) {
				if (bullets[i] != nullptr && !bullets[i]->isActive()) {
					delete bullets[i];
					bullets[i] = nullptr;
					bullets.erase(bulletIT);
					erased = true;
				}
			}
		}
		i++;
		if (!erased)
			bulletIT++;
	}
}

void StarWarsBulletManager::render(Uint32 time)
{
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->isActive())
			bullets[i]->render(time);
	}
}

Bullet* StarWarsBulletManager::getBullet() {
	bool found_ = false;
	int i = 0;

	while (i < bullets.size() && !found_) {
		if (!(bullets[i]->isActive()))
			found_ = true;
		else
			i++;
	}

	if (found_) {
		return bullets[i];
	}
	else {
		Bullet* bullet = new Bullet(game_);
		//decision de diseño, no comparten la misma instancia de los components, cada bala tiene una
		//porque si no cuando se destruye una bala al salir de la pared, la destructora elimina la instancia
		//del component y las demas balas se quedan sin component
		bullet->addRenderComponent(new ImageRenderer(game_->getResources()->getImageTexture(Resources::Laser)));
		bullet->addPhysicsComponent(new BasicMotionPhysics());
		bullets.push_back(bullet);

		return bullet;
	}
}

void StarWarsBulletManager::initBullets() {
	for (int i = 0; i < numOfBullets_; i++) {
		Bullet* b = getBullet();
	}

	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->setActive(false);
}

void StarWarsBulletManager::receive(Message* msg)
{
	BulletAstroidCollision * bac;
	Asteroid* ast;
	Bullet* bul;
	FighterIsShooting* fis;
	Fighter* fightr;
	Vector2D bulletPos;
	Vector2D bulletVel;
	Vector2D v(0, 0);
	bool destroy;

	switch (msg->id_) {
	case ROUND_START:
		clear();
		initBullets();
		break;

	case ROUND_OVER:
		clear();
		break;

	case BULLET_ASTROID_COLLISION:
		bac = static_cast<BulletAstroidCollision*>(msg);
		bul = bac->bullet_;

		destroy = bac->destroy_;
		if (destroy)
			bul->setActive(false);

		break;

	case BULLET_FIGHTER_COLLISION:
		break;

	case FIGHTER_SHOOT:
		fis = static_cast<FighterIsShooting*>(msg);
		fightr = fis->fighter_;
		bulletPos = fis->bulletPosition_;
		bulletVel = fis->bulletVelocity_;
		shoot(fightr, bulletPos, bulletVel);
		break;
	}
}

void StarWarsBulletManager::clear() {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i] != nullptr)
			delete bullets[i];
		bullets[i] = nullptr;
	}
	bullets.clear();
}