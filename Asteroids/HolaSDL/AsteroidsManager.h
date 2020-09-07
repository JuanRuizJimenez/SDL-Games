#pragma once
#include "GameObject.h"
#include "Observable.h"
#include "Observer.h"
#include "ImageRenderer.h"
#include "CircularMotionPhysicsComponent.h"
#include "RotationPhysicsComponent.h"

class AsteroidsManager : public GameObject, public Observer, public Observable {
public:
	AsteroidsManager(SDLGame* game);
	virtual ~AsteroidsManager();
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual vector<Asteroid*>& getAsteroids() { return asteroids_; };
	virtual void receive(Message* msg);
	void clear();
	void addObserver(Observer* o) { registerObserver(o); };
private:
	Asteroid* getAsteroid();
	void initAsteroids();

	vector<Asteroid*> asteroids_;
	int numOfAsteroids_;
	int iniNumOfAsteroids_;
};

