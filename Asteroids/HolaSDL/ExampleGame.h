#ifndef EXAMPLEGAME_H_
#define EXAMPLEGAME_H_

#include <vector>
#include "SDLGame.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "ComponentSwitcher.h"
#include "Container.h"
#include "SoundManager.h"
#include "StarWarsBulletManager.h"
#include "checkML.h"
#include "FullRenderer.h"
#include "Fighter.h"
#include "Asteroid.h"
#include "AsteroidsManager.h"
#include "FightersManager.h"
#include "CollisionManager.h"
#include "Observable.h"
#include "ShootBar.h"
#include "LifeBar.h"
#include "GameManager.h"

class ExampleGame: public SDLGame, public Observable, public Observer {

public:
	ExampleGame();
	virtual ~ExampleGame();

	// from SDLGame
	void start();
	void stop();
	void receive(Message* msg);

private:
	void initGame();
	void closeGame();
	void handleInput(Uint32 time);
	void update(Uint32 time);
	void render(Uint32 time);

	const static int _WINDOW_WIDTH_ = 1280;
	const static int _WINDOW_HEIGHT_ = 940;
	bool exit_;
	bool keep_;
	std::vector<GameObject*> actors_;

	Fighter* ship_;
	Container* background_;
	Container* hud_;
	Container* scoreHud_;
	Container* badget1_;
	Container* badget2_;
	Container* badget3_;
	Container* badget4_;
	Container* badget5_;
	ShootBar* bar_;
	LifeBar* life_;

	RenderComponent* backgRC_;
	RenderComponent* hudRC_;
	RenderComponent* barRC_;
	RenderComponent* lifeRC_;
	RenderComponent* scoreRC_;

	ComponentSwitcher* cs_;

	SoundManager soundManager_;
	//decision de diseño, estos managers son punteros para poder
	//actualizar su logica desde el vector actors_ y poder borrarlos
	//todos de una tirada
	AsteroidsManager* asteroidsManager_;
	StarWarsBulletManager* swbm_;
	FightersManager* fightersManager_;
	CollisionManager* colisionManager_;
	GameManager* gameManager_;
	BonusManager* bonusManager_;
};

#endif /* EXAMPLEGAME_H_ */
