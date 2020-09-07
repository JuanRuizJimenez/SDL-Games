#pragma once
#include "Container.h"
#include "Observer.h"
#include "Observable.h"
#include "Bonus.h"
#include <ctime>

class BonusManager : public Container, public Observer, public Observable
{
public:
	BonusManager(SDLGame* game, Observer* g, Observer* lifeBar, Observer* fm);
	virtual ~BonusManager();
	std::vector<Bonus*> getBonuses() { return bonuses_; }
	virtual void receive(Message* msg);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	void resetTime() {
		t = clock();
		timeInterval_ = 5;
		iniTimeInterval_ = timeInterval_;
	}
private:
	std::vector<Bonus*> bonuses_;
	bool powerup = false;
	double secondsPassed_;
	double timeInterval_;
	double iniTimeInterval_;
	clock_t t;
};

