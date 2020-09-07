#include "GameManager.h"

GameManager::GameManager(SDLGame* game, Observer* lifeBar, Observer* bm, 
	Observer* am, Observer* fm, Observer* g, Observer* sm) : Container(game)
{
	registerObserver(lifeBar);
	registerObserver(bm);
	registerObserver(am);
	registerObserver(fm);
	registerObserver(g);
	registerObserver(sm);
	registerObserver(this);

	score_ = 0;
	running_ = false;
	gameOver_ = false;

	scoreRenderer_ = new ScoreRenderer();
	gameMsg_ = new GameMsgRenderer();
	gcIC_ = new GameCtrlInputComponent();
	badgeTimer_ = new BadgeTimer();

	addRenderComponent(scoreRenderer_);
	addRenderComponent(gameMsg_);
	addInputComponent(gcIC_);
	addPhysicsComponent(badgeTimer_);
}

GameManager::~GameManager()
{
}

bool GameManager::isGameOver() const {
	return gameOver_;
}

int GameManager::getScore() const {
	return score_;;
}

bool GameManager::isRunning() const {
	return running_;
}

void GameManager::setRunning(bool running) {
	if (running_ != running) {
		running_ = running;

		Message m = { running ? ROUND_START : ROUND_OVER };
		send(&m);
		if (gameOver_ && running)
			gameOver_ = false;
	}
}

void GameManager::setBadge(bool b) {
	if (b) {
		MessageId id = BADGE_ON;
		Message m(id);
		send(&m);
	}
	else {
		badgeTimer_->stop();
		MessageId id2 = BADGE_OFF;
		Message m2(id2);
		send(&m2);
	}
}

void GameManager::receive(Message* msg) {
	Fighter* fightr;
	AstroidFighterCollision* afc;
	
	MessageId id3 = ROUND_START;
	Message m3(id3);

	GoDownLifeBar m2(nullptr);

	MessageId id = ROUND_OVER;
	Message m(id);

	MessageId id4 = END_PARTY;
	Message m4(id4);

	MessageId id5 = RESTART_BARLIFE;
	Message m5(id5);

	MessageId id6 = BADGE_ON;
	Message m6(id6);

	SDL_Rect rect;

	switch (msg->id_) {
	case ASTROID_FIGHTER_COLLISION:
		afc = static_cast<AstroidFighterCollision*>(msg);
		fightr = afc->fighter_;
		fightr->setLives(fightr->getLives() - 1);
		m2 = GoDownLifeBar(fightr);
		send(&m2);

		SDL_RenderClear(getGame()->getRenderer());
		SDL_RenderPresent(getGame()->getRenderer());
		send(&m);
		SDL_Delay(500);

		if (fightr->getLives() > 0) {
			send(&m3);
		}
		else {
			send(&m4);
			score_ = 0;
			fightr->setLives(fightr->getMaxLives());
			send(&m5);
		}

		break;

	case BULLET_ASTROID_COLLISION:
		score_ += 10;
		cont_++;
		if (cont_ >= 10) {
			badgeTimer_->start(7000);
			send(&m6);
			cont_ = 0;
		}
		break;

	case NO_MORE_ATROIDS:
		send(&m4);
		send(&m);
		break;

	case ROUND_START:
		cont_ = 0;
		break;
	}
}
