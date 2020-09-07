#pragma once
#include "Container.h"
#include "Observer.h"
#include "Observable.h"
#include "ScoreRenderer.h"
#include "ScoreRenderer.h"
#include "GameMsgRenderer.h"
#include "GameCtrlInputComponent.h"
#include "BadgeTimer.h"
#include "Bonus.h"
#include "AleatoryPhysicsComponent.h"
#include "ImageRenderer.h"
#include "RotationPhysicsComponent.h"

class GameManager : public Container, public Observer, public Observable 
{
public:
	GameManager(SDLGame* game, Observer* lifeBar, Observer* bm, Observer* am, Observer* fm, Observer* g, Observer* sm);
	virtual ~GameManager();
	bool isGameOver() const;
	bool isRunning() const;
	void setRunning(bool running);
	int getScore() const;
	void setBadge(bool b);
	void receive(Message* msg);

private:
	ScoreRenderer* scoreRenderer_;
	GameMsgRenderer* gameMsg_;
	GameCtrlInputComponent* gcIC_;
	BadgeTimer* badgeTimer_;

	int score_;
	int cont_;
	bool gameOver_;
	bool running_;

	Bonus* bonus_;
};