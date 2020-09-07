#include "FightersManager.h"
#include "RotationInputComponent.h"
#include "CircularMotionPhysicsComponent.h"
#include "AcelerationInputComponent.h"
#include "AcelerationInputComponent2.h"
#include "GunInputComponent.h"
#include "MiniGunInputComponent.h"

FightersManager::FightersManager(SDLGame* game, Observer* bulletsMamager, Observer* asteroidsManager, 
	Observer* shootBar) : GameObject(game)
{
	registerObserver(bulletsMamager);
	registerObserver(asteroidsManager);
	registerObserver(this);

	fighter_ = new Fighter(game, 0);
	fighter_->setActive(false);
	fighter_->setWidth(70); fighter_->setHeight(70);
	fighter_->setPosition(Vector2D(game->getWindowWidth() / 2 - fighter_->getWidth(), game->getWindowHeight() / 2 - fighter_->getHeight()));
	Vector2D v(0, -1);
	fighter_->setDirection(v);

	shipRC_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::Ship)); //normal
	epicShipRC_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::Ship3)); //special
	megaShipRC_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::Ship6)); //special
	hiperShipRC_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::Ship4)); //special
	ultraShipRC_ = new ImageRenderer(game->getResources()->getImageTexture(Resources::Ship5)); //special

	shipRotateIC_ = new RotationInputComponent(SDLK_RIGHT, SDLK_LEFT, 10); //normal
	shipAcelerationIC_ = new AcelerationInputComponent2(SDLK_UP, SDLK_DOWN, 0.25, 2, 0.75); //normal
	shipGunIC_ = new GunInputComponent(SDLK_SPACE, bulletsMamager, shootBar, 5, 3.5); //normal
	megaShipGunIC_ = new GunInputComponent(SDLK_SPACE, bulletsMamager, shootBar, 20000, 1); //special
	hiperShipGunIC_ = new MiniGunInputComponent(SDLK_SPACE, bulletsMamager, shootBar, 5, 3.5, 6); //special
	epicShipAcelerationIC_ = new AcelerationInputComponent(SDLK_UP, SDLK_DOWN, 0, 2, 0.75, 0.5); //special

	shipToroidPC_ = new CircularMotionPhysicsComponent(); //normal

	//create component switcher
	cs_ = new ComponentSwitcher(game, fighter_, SDLK_RETURN);
	cs_->addMode({ shipAcelerationIC_, shipRotateIC_, shipGunIC_, shipToroidPC_, shipRC_, shipRC_ });
	cs_->addMode({ epicShipAcelerationIC_, shipRotateIC_, shipGunIC_, shipToroidPC_, epicShipRC_, epicShipRC_ });
	cs_->addMode({ shipAcelerationIC_, shipRotateIC_, megaShipGunIC_, shipToroidPC_, megaShipRC_, megaShipRC_ });
	cs_->addMode({ shipAcelerationIC_, shipRotateIC_, hiperShipGunIC_, shipToroidPC_, hiperShipRC_, hiperShipRC_ });
	cs_->addMode({ shipAcelerationIC_, shipRotateIC_, shipGunIC_, shipToroidPC_, ultraShipRC_, ultraShipRC_ });
	cs_->setMode(0);
	Vector2D p(87, 40); Vector2D d(0, -1);
	cs_->setPosition(p); cs_->setDirection(d);
	cs_->setWidth(100); cs_->setHeight(100);
}

FightersManager::~FightersManager()
{
	cs_->setMode(0);

	//special components must be deleted here
	if (epicShipAcelerationIC_ != nullptr) delete epicShipAcelerationIC_;
	if (epicShipRC_ != nullptr) delete epicShipRC_;
	if (megaShipGunIC_ != nullptr) delete megaShipGunIC_;
	if (megaShipRC_ != nullptr) delete megaShipRC_;
	if (hiperShipGunIC_ != nullptr) delete hiperShipGunIC_;
	if (hiperShipRC_ != nullptr) delete hiperShipRC_;
	if (ultraShipRC_ != nullptr) delete ultraShipRC_;
}

void FightersManager::receive(Message* msg) {
	AstroidFighterCollision* afc;
	SetMode* sm;
	Fighter* fightr;
	Asteroid* ast;
	Vector2D v(0, 0);
	Vector2D d(0, -1);

	switch (msg->id_) {
	case ROUND_START:
		fighter_->setActive(true);
		fighter_->setWidth(70); fighter_->setHeight(70);
		fighter_->setPosition(Vector2D(getGame()->getWindowWidth() / 2 - fighter_->getWidth(), getGame()->getWindowHeight() / 2 - fighter_->getHeight()));
		fighter_->setDirection(d);
		fighter_->setVelocity(v);
		break;
	case ROUND_OVER:
		fighter_->setActive(false);
		fighter_->setVelocity(v);
		break;
	case BADGE_ON:
		if (badgesCounter_ == 0) {
			cs_->setMode(2);
			badgesCounter_++;
		}
		else if (badgesCounter_ == 1) {
			cs_->setMode(3);
			badgesCounter_++;
		}
		else if (badgesCounter_ == 2) {
			cs_->setMode(4);
			badgesCounter_ = 0;
		}
		break;
	case BADGE_OFF:
		cs_->setMode(0);
		break;
	case AGILE_ON:
		cs_->setMode(1);
		break;
	case AGILE_OFF:
		cs_->setMode(0);
		break;
	case ASTROID_FIGHTER_COLLISION:
		cs_->setMode(0);
		afc = static_cast<AstroidFighterCollision*>(msg);
		fightr = afc->fighter_;
		ast = afc->astroid_;
		fightr->setPosition(Vector2D(getGame()->getWindowWidth() / 2 - fightr->getWidth(), getGame()->getWindowHeight() / 2 - fightr->getHeight()));
		fightr->setVelocity(v); fightr->setDirection(d);
		ast->setPosition(v);
		break;

	case SET_MODE:
		sm = static_cast<SetMode*>(msg);
		cs_->setMode(sm->mode_);
		break;
	}
}