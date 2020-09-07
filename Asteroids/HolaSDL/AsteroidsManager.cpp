#include "AsteroidsManager.h"
#include "messages.h"
#include <stdlib.h>
#include <time.h>

AsteroidsManager::AsteroidsManager(SDLGame* game) : GameObject(game)
{
	srand(time(NULL));

	numOfAsteroids_ = rand() % 6 + 5;
	//numOfAsteroids_ = 1;
	iniNumOfAsteroids_ = numOfAsteroids_;
}

AsteroidsManager::~AsteroidsManager()
{
	clear();
}

void AsteroidsManager::update(Uint32 time) {
	for (Asteroid* a : asteroids_) {
		if (a->isActive())
			a->update(time);
		else {
			a->setWidth(70);
			a->setHeight(70);
			int gen = rand() % 2 + 1;
			a->setGenerations(gen);
		}
	}
}

void AsteroidsManager::render(Uint32 time) {
	for (Asteroid* a : asteroids_) {
		if (a->isActive())
			a->render(time);
	}
}

Asteroid* AsteroidsManager::getAsteroid() {
	bool found_ = false;
	int i = 0;

	while (i < asteroids_.size() && !found_) {
		if (!(asteroids_[i]->isActive()))
			found_ = true;
		else 
		    i++;
	}

	if (found_) {
		return asteroids_[i];
	}
	else {
		Asteroid* ast = new Asteroid(getGame());
		ast->addPhysicsComponent(new CircularMotionPhysicsComponent());
		ast->addPhysicsComponent(new RotationPhysicsComponent());
		ast->addRenderComponent(new ImageRenderer(getGame()->getResources()->getImageTexture(Resources::Asteroid)));

		int gen = rand() % 2 + 1;
		ast->setGenerations(gen);

		asteroids_.push_back(ast);

		return ast;
	}
}

void AsteroidsManager::initAsteroids() {
	for (int i = 0; i < asteroids_.size(); i++)
		asteroids_[i]->setActive(false);

	for (int i = 0; i < iniNumOfAsteroids_; i++) {
		Asteroid* ast = getAsteroid();
		ast->setWidth(70); ast->setHeight(70);

		Vector2D position; double posX; double posY;
		posX = rand() % getGame()->getWindowWidth();
		posY = rand() % getGame()->getWindowHeight();
		position.setX(posX); position.setY(posY);
		ast->setPosition(position);

		Vector2D velocity; double velX; double velY;
		velX = rand() % 10; velX = velX * 0.1;
		velY = rand() % 10; velY = velY * 0.1;
		velocity.setX(velX); velocity.setY(velY);
		ast->setVelocity(velocity);

		ast->setActive(true);
	}
}

void AsteroidsManager::receive(Message* msg) {
	BulletAstroidCollision * bac;
	Asteroid* ast;
	Bullet* bul;
	Fighter* fightr;

	Vector2D pos;
	Vector2D vel;
	Vector2D dir;
	Vector2D v(0, 0);

	double width;
	double height;
	int degrees;

	MessageId id = NO_MORE_ATROIDS;
	Message m(id);

	switch (msg->id_) {
	case BULLET_ASTROID_COLLISION:
		bac = static_cast<BulletAstroidCollision*>(msg);
		ast = bac->astroid_;
		bul = bac->bullet_;
 
		ast->setActive(false);

		numOfAsteroids_--;
		degrees = rand() % 20 + 10;

		if (ast->getGenerations() > 0) {
			int children = rand() % 2 + 2;
			width = ast->getWidth() * 2 / 3;
			height = ast->getHeight() * 2 / 3;

			for (int i = 0; i < children; i++) {
				pos = ast->getPosition();
				vel = ast->getVelocity();
				dir = ast->getDirection();

				Asteroid* nAst = getAsteroid();
				nAst->setGenerations(ast->getGenerations() - 1);
		
				vel.rotate(degrees);
				nAst->setVelocity(vel);

				dir.rotate(degrees);
				nAst->setDirection(dir);

				nAst->setPosition(pos);

				nAst->setWidth(width);
				nAst->setHeight(height);

				nAst->setActive(true);
				numOfAsteroids_++;

				degrees += 20;
			}
		}
		if (numOfAsteroids_ == 0) {
			send(&m);
		}

		break;

	case ROUND_START:
		initAsteroids();
		break;

	case ROUND_OVER:
		for (int i = 0; i < asteroids_.size(); i++) {
			if (asteroids_[i] != nullptr)
				asteroids_[i]->setActive(false);
		}
		numOfAsteroids_ = iniNumOfAsteroids_;
		break;
	}
}

void AsteroidsManager::clear() {
	for (int i = 0; i < asteroids_.size(); i++) {
		if (asteroids_[i] != nullptr)
			delete asteroids_[i];
		asteroids_[i] = nullptr;
	}
	asteroids_.clear();
}