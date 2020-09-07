#include "LifeBar.h"

LifeBar::LifeBar(SDLGame* game, double w) : Container(game)
{
	iniW_ = w;
}

LifeBar::~LifeBar()
{
}

void LifeBar::receive(Message* msg) {
	GoDownLifeBar* gdb;
	Fighter* fightr;
	double less, plus, widht;
	int lessLives, actLives;
	Vector2D pos;
	iniPosX_ = this->getPosition().getX();

	switch (msg->id_) {
	case BAR_LIFE:
		gdb = static_cast<GoDownLifeBar*>(msg);
		fightr = gdb->fighter_;

		less = iniW_ / fightr->getMaxLives();
		widht = iniW_;

		lessLives = fightr->getMaxLives() - fightr->getLives();
		for (int i = 0; i < lessLives; i++)
			widht -= less;

		this->setWidth(widht);

		pos.setX(iniPosX_);
		pos.setY(this->getPosition().getY());
		break;

	case RESTART_BARLIFE:
		this->setWidth(iniW_);
		break;

	case UPLIFE:
		gdb = static_cast<GoDownLifeBar*>(msg);
		fightr = gdb->fighter_;

		plus = iniW_ / fightr->getMaxLives();
		widht = 0;

		if (fightr->getLives() < fightr->getMaxLives())
			fightr->setLives(fightr->getLives() + 1);

		actLives = fightr->getLives();
		for (int i = 0; i < actLives; i++)
			widht += plus;

		this->setWidth(widht);

		pos.setX(iniPosX_);
		pos.setY(this->getPosition().getY());
		break;
	}
}