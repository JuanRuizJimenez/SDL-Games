#include "BonusManager.h"
#include "ImageRenderer.h"
#include "RotationPhysicsComponent.h"
#include "AleatoryPhysicsComponent.h"

BonusManager::BonusManager(SDLGame* game, Observer* g, Observer* lifeBar, Observer* fm) : Container(game)
{
	registerObserver(g);
	registerObserver(lifeBar);
	registerObserver(fm);

	t = clock();
	timeInterval_ = 10;
	iniTimeInterval_ = timeInterval_;
}

BonusManager::~BonusManager()
{
	for (Bonus* b : bonuses_) {
		if (b != nullptr)
			delete b;
	}
}

void BonusManager::update(Uint32 time) {
	for (GameObject* o : bonuses_) {
		if (o->isActive())
			o->update(time);
	}

	if (powerup) {
		secondsPassed_ = (clock() - t) / CLOCKS_PER_SEC;
		if (secondsPassed_ >= timeInterval_) {
			timeInterval_ += iniTimeInterval_;
			powerup = false;
			SetMode sm(0);
			send(&sm);
		}
	}
	else
	{
		resetTime();
	}
}

void BonusManager::render(Uint32 time) {
	for (GameObject* o : bonuses_) {
		if (o->isActive())
			o->render(time);
	}
}

void BonusManager::receive(Message* msg) 
{
	Bullet* bll;
	Bonus* bonus_;
	Fighter* fig;
	FighterBonusCollision* fbc;

	GoUpLifeBar m(nullptr);
	SetMode sm0(0);
	SetMode sm1(1);
	SetMode sm2(2);
	SetMode sm3(3);
	SetMode sm4(4);

	CreateBonus* cb;

	switch (msg->id_)
	{
	case FIGHTER_BONUS_COLLISION:
		fbc = static_cast<FighterBonusCollision*>(msg);

		bonus_ = fbc->bonus_;
		fig = fbc->fighter_;

		bonus_->setActive(false);

		switch (bonus_->id_)
		{
		case LIFE_BONUS:
			m = GoUpLifeBar(fig);
			send(&m);
			send(&m);
			send(&m);
			send(&m);
			break;
		case FEATHER_BONUS:
			send(&sm1);
			powerup = true;
			resetTime();
			break;
		case BOMB_BONUS:
			send(&sm2);
			powerup = true;
			resetTime();
			break;
		case TWHOMP_BONUS:
			send(&sm3);
			powerup = true;
			resetTime();
			break;
		case BILL_BONUS:
			send(&sm4);
			powerup = true;
			resetTime();
			break;
		}

		break;
		
	case CREATE_BONUS:
		cb = static_cast<CreateBonus*>(msg);
		Vector2D position = cb->asteroid_->getPosition();

		SDLGame * game = this->getGame();
		Bonus* bonus_ = new Bonus(game);
		bonus_->setPosition(position);
		bonus_->setWidth(35);
		bonus_->setHeight(35);
		bonus_->addPhysicsComponent(new RotationPhysicsComponent());

		switch (bonus_->id_)
		{
		case LIFE_BONUS:
			bonus_->addRenderComponent(new ImageRenderer(game->getResources()->getImageTexture(Resources::UP)));
			bonus_->addPhysicsComponent(new AleatoryPhysicsComponent());
			break;
		case FEATHER_BONUS:
			bonus_->addRenderComponent(new ImageRenderer(game->getResources()->getImageTexture(Resources::Feather)));
			break;
		case BOMB_BONUS:
			bonus_->addRenderComponent(new ImageRenderer(game->getResources()->getImageTexture(Resources::Bomb)));
			break;
		case TWHOMP_BONUS:
			bonus_->addRenderComponent(new ImageRenderer(game->getResources()->getImageTexture(Resources::Thwomp)));
			break;
		case BILL_BONUS:
			bonus_->addRenderComponent(new ImageRenderer(game->getResources()->getImageTexture(Resources::Bill)));
			break;
		}
		
		bonuses_.push_back(bonus_);
	}
}
