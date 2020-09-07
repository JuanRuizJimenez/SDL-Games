#include "CollisionManager.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

CollisionManager::CollisionManager(SDLGame* game, BulletsManager* bulletsManager,
	AsteroidsManager* asteroidManager, FightersManager* fightersManager, 
	GameManager* gm, BonusManager* bonm, Observer* sm) : GameObject(game),
	bulletsManager_(bulletsManager), asteroidsManager_(asteroidManager), fightersManager_(fightersManager),
	gameManager_(gm), bonusManager_(bonm)
{
	Observer* am = asteroidManager; 
	Observer* bm = bulletsManager; 
	Observer* fm = fightersManager;
	registerObserver(am);
	registerObserver(bm);
	registerObserver(fm);
	registerObserver(gm);
	registerObserver(sm);
	registerObserver(bonm);

	srand(time(NULL));
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::update(Uint32 time) {
	vector<Bullet*> bullets = bulletsManager_->getBullets();
	vector<Asteroid*> asteroids = asteroidsManager_->getAsteroids();
	Fighter* fighter = fightersManager_->getFighter();
	std::vector<Bonus*> bonuses = bonusManager_->getBonuses();

	//fighter VS asteroids
	bool pum = false;
	int i = 0;
	while (i < asteroids.size() && !pum) {
		//collides is collidesWithRotation
		if (Collisions::collides(fighter, asteroids[i]) && asteroids[i]->isActive())
			pum = true;
		else
			i++;
	}
	if (pum) {
		AstroidFighterCollision m(asteroids[i], fighter);
		send(&m);
	}

	//bullets VS asteroids
	int j = 0;
	int jj = 0;
	while (j < bullets.size()){
		while (jj < asteroids.size()) {
			if (Collisions::collides(bullets[j], asteroids[jj]) && bullets[j]->isActive() && asteroids[jj]->isActive()) {
				Bullet* b = bullets[j];
				Asteroid* a = asteroids[jj];

				if (fightersManager_->getCS()->getMode() != 4) {
					BulletAstroidCollision m2(b, a, true);
					send(&m2);
				}
				else {
					BulletAstroidCollision m2(b, a, false);
					send(&m2);
				}

				if (rand() % 4 == 0) {
					CreateBonus mb(asteroids[jj]);
					send(&mb);
				}
			}
			jj++;
		}
		j++;
		jj = 0;
	}

	//fighter VS bonus
	int a = 0;
	int b = 0;
	bool pichium = false;
	while (b < bonuses.size()) {
		if (Collisions::collides(fighter, bonuses[b]) && fighter->isActive() && bonuses[b]->isActive()) {
			if (fightersManager_->getCS()->getMode() != 4) {
				FighterBonusCollision m4(bonuses[b], fighter);
				send(&m4);
			}
			else {
				FighterBonusCollision m4(bonuses[b], fighter);
				send(&m4);
			}
			pichium = true;
		}
		b++;
	}
}