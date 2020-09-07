#include "ShootBar.h"

ShootBar::ShootBar(SDLGame* game, double w) : Container(game)
{
	iniW_ = w;
}

ShootBar::~ShootBar()
{
}

void ShootBar::receive(Message* msg) {
	GoDownBar* gdb;
	Fighter* fightr;
	int shotsRealiced, maxShots;
	double less, widht;
	Vector2D pos;
	iniPosX_ = this->getPosition().getX();

	switch (msg->id_) {
	case BAR_SHOOT:
		gdb = static_cast<GoDownBar*>(msg);
		fightr = gdb->fighter_;
		shotsRealiced = gdb->shotsRealized_;
		maxShots = gdb->maxShots_;

		less = iniW_ / maxShots;
		widht = iniW_;
		for (int i = 0; i < shotsRealiced; i++)
			widht -= less;

		this->setWidth(widht);

		pos.setX(iniPosX_);
		pos.setY(this->getPosition().getY());
		break;

	case RESTART_BAR:
		this->setWidth(iniW_);
		break;
	}
}
