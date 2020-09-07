#pragma once
#include "GameObject.h"
#include "Observer.h"
#include "Observable.h"
#include "ComponentSwitcher.h"

class FightersManager : public GameObject, public Observer, public Observable
{
public:
	FightersManager(SDLGame* game, Observer* bulletsMamager, Observer* asteroidsManager, 
		Observer* shootBar);
	virtual ~FightersManager();
	//decision de diseño, los metodos handle input, update y render seran llamados
	//desde el bucle de juego ya que el caza es un actor mas
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual void update(Uint32 time) {};
	virtual void render(Uint32 time) {};
	Fighter* getFighter() { return fighter_; };
	ComponentSwitcher* getCS() { return cs_; };
	virtual void receive(Message* msg);
private:
	Fighter* fighter_;
	
	RenderComponent* shipRC_; //normal
	RenderComponent* epicShipRC_; //special
	RenderComponent* megaShipRC_; //special
	RenderComponent* hiperShipRC_; //special
	RenderComponent* ultraShipRC_; //special

	InputComponent* shipRotateIC_; //normal
	InputComponent* shipAcelerationIC_; //normal
	InputComponent* shipGunIC_; //normal
	InputComponent* megaShipGunIC_; //special
	InputComponent* hiperShipGunIC_; //special
	InputComponent* epicShipAcelerationIC_; //special

	PhysicsComponent* shipToroidPC_; //normal

	ComponentSwitcher* cs_;

	int badgesCounter_ = 0;
};

