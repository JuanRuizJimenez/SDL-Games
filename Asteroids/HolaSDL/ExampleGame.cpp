#include "ExampleGame.h"
#include "Collisions.h"
#include "ImageRenderer.h"
#include "ScoreRenderer.h"
#include "RotationInputComponent.h"
#include "CircularMotionPhysicsComponent.h"
#include "AcelerationInputComponent.h"
#include "AcelerationInputComponent2.h"
#include "GunInputComponent.h"
#include "messages.h"
#include "XboxController.h"

ExampleGame::ExampleGame() : SDLGame("ASTEROIDS", _WINDOW_WIDTH_, _WINDOW_HEIGHT_), soundManager_(this)
{
	initGame();
	exit_ = false;
}

ExampleGame::~ExampleGame() {
	closeGame();
}

void ExampleGame::initGame() {

	// hide cursor
	SDL_ShowCursor(0);

	//create background
	background_ = new Container(this);
	backgRC_ = new FullRenderer(getResources()->getImageTexture(Resources::Background));
	background_->addRenderComponent(backgRC_);
	actors_.push_back(background_);

	//create bullets manager
	swbm_ = new StarWarsBulletManager(this, &soundManager_);
	actors_.push_back(swbm_);

	//create asteroids manager
	asteroidsManager_ = new AsteroidsManager(this);
	actors_.push_back(asteroidsManager_);

	//create shoot bar
	Texture* barTx = getResources()->getImageTexture(Resources::Shoot);
	SDL_SetTextureAlphaMod(barTx->getText(), 180);
	barRC_ = new ImageRenderer(barTx);
	double wid = 400;
	bar_ = new ShootBar(this, wid);
	bar_->setWidth(wid); bar_->setHeight(20);
	Vector2D bp(380, 112); bar_->setPosition(bp);
	Vector2D bd(0, -1); bar_->setDirection(bd);
	bar_->addRenderComponent(barRC_);

	//create life bar
	Texture* lifeTx = getResources()->getImageTexture(Resources::Life);
	SDL_SetTextureAlphaMod(lifeTx->getText(), 180);
	lifeRC_ = new ImageRenderer(lifeTx);
	double wid2 = 400;
	life_ = new LifeBar(this, wid);
	life_->setWidth(wid2); life_->setHeight(20);
	Vector2D lp(380, 17); life_->setPosition(lp);
	Vector2D ld(0, -1); life_->setDirection(ld);
	life_->addRenderComponent(lifeRC_);

	//create fighters manager
	fightersManager_ = new FightersManager(this, swbm_, asteroidsManager_, bar_);
	actors_.push_back(fightersManager_);

	//create bonus manager
	bonusManager_ = new BonusManager(this, this, life_, fightersManager_);
	actors_.push_back(bonusManager_);

	//create game manager
	gameManager_ = new GameManager(this, life_, swbm_, asteroidsManager_, fightersManager_, this, &soundManager_);
	asteroidsManager_->addObserver(gameManager_); //to avoid dependences

	//create collisions manager
	colisionManager_ = new CollisionManager(this, swbm_, asteroidsManager_, fightersManager_, gameManager_, bonusManager_, &soundManager_);
	actors_.push_back(colisionManager_);

	//create ship
	ship_ = fightersManager_->getFighter();
	actors_.push_back(ship_);

	//create hud
	Texture* hudTx = getResources()->getImageTexture(Resources::HUD);
	SDL_SetTextureAlphaMod(hudTx->getText(), 180);
	hudRC_ = new ImageRenderer(hudTx);
	hud_ = new Container(this);
	hud_->setWidth(800); hud_->setHeight(150);
	Vector2D hp(0, 0); hud_->setPosition(hp);
	Vector2D hd(0, -1); hud_->setDirection(hd);
	hud_->addRenderComponent(hudRC_);
	actors_.push_back(hud_);

	//create scoreHud
	Texture* scTx = getResources()->getImageTexture(Resources::HUD2);
	SDL_SetTextureAlphaMod(scTx->getText(), 180);
	scoreRC_ = new ImageRenderer(scTx);
	scoreHud_ = new Container(this);
	scoreHud_->setWidth(getWindowWidth() - 800); scoreHud_->setHeight(150);
	Vector2D sp(800, 0); scoreHud_->setPosition(sp);
	Vector2D sd(0, -1); scoreHud_->setDirection(sd);
	scoreHud_->addRenderComponent(scoreRC_);
	actors_.push_back(scoreHud_);

	//push bar here (z order)
	actors_.push_back(bar_);

	//push bar here (z order)
	actors_.push_back(life_);

	//push gm here (z order)
	actors_.push_back(gameManager_);

	//create component switcher
	cs_ = fightersManager_->getCS();
	actors_.push_back(cs_);

	//create badgets
	badget1_ = new Container(this);
	Vector2D pos(545, 57);
	Vector2D dir(0, -1);
	Vector2D vel(0, 0);
	double width = 60;
	double height = 40;
	Texture* t = getResources()->getImageTexture(Resources::Champ);
	SDL_SetTextureAlphaMod(t->getText(), 180);
	RenderComponent* rc = new ImageRenderer(t);

	badget1_->setPosition(pos);
	badget1_->setDirection(dir);
	badget1_->setVelocity(vel);
	badget1_->setWidth(width);
	badget1_->setHeight(height);
	badget1_->addRenderComponent(rc);
	actors_.push_back(badget1_);

	badget2_ = new Container(this);
	Vector2D pos2(545, 59);
	Vector2D dir2(0, -1);
	Vector2D vel2(0, 0);
	double width2 = 50;
	double height2 = 30;
	Texture* t2 = getResources()->getImageTexture(Resources::Feather);
	SDL_SetTextureAlphaMod(t2->getText(), 180);
	RenderComponent* rc2 = new ImageRenderer(t2);

	badget2_->setPosition(pos2);
	badget2_->setDirection(dir2);
	badget2_->setVelocity(vel2);
	badget2_->setWidth(width2);
	badget2_->setHeight(height2);
	badget2_->addRenderComponent(rc2);
	actors_.push_back(badget2_);
	badget2_->setActive(false);

	badget3_ = new Container(this);
	Vector2D pos3(545, 57);
	Vector2D dir3(0, -1);
	Vector2D vel3(0, 0);
	double width3 = 60;
	double height3 = 40;
	Texture* t3 = getResources()->getImageTexture(Resources::Bomb);
	SDL_SetTextureAlphaMod(t3->getText(), 180);
	RenderComponent* rc3 = new ImageRenderer(t3);

	badget3_->setPosition(pos3);
	badget3_->setDirection(dir3);
	badget3_->setVelocity(vel3);
	badget3_->setWidth(width3);
	badget3_->setHeight(height3);
	badget3_->addRenderComponent(rc3);
	actors_.push_back(badget3_);
	badget3_->setActive(false);

	badget4_ = new Container(this);
	Vector2D pos4(555, 60);
	Vector2D dir4(0, -1);
	Vector2D vel4(0, 0);
	double width4 = 50;
	double height4 = 30;
	Texture* t4 = getResources()->getImageTexture(Resources::Thwomp);
	SDL_SetTextureAlphaMod(t4->getText(), 180);
	RenderComponent* rc4 = new ImageRenderer(t4);

	badget4_->setPosition(pos4);
	badget4_->setDirection(dir4);
	badget4_->setVelocity(vel4);
	badget4_->setWidth(width4);
	badget4_->setHeight(height4);
	badget4_->addRenderComponent(rc4);
	actors_.push_back(badget4_);
	badget4_->setActive(false);

	badget5_ = new Container(this);
	Vector2D pos5(555, 60);
	Vector2D dir5(0, -1);
	Vector2D vel5(0, 0);
	double width5 = 50;
	double height5 = 30;
	Texture* t5 = getResources()->getImageTexture(Resources::Bill);
	SDL_SetTextureAlphaMod(t5->getText(), 180);
	RenderComponent* rc5 = new ImageRenderer(t5);

	badget5_->setPosition(pos5);
	badget5_->setDirection(dir5);
	badget5_->setVelocity(vel5);
	badget5_->setWidth(width5);
	badget5_->setHeight(height5);
	badget5_->addRenderComponent(rc5);
	actors_.push_back(badget5_);
	badget5_->setActive(false);

	//observers
	registerObserver(asteroidsManager_);
	registerObserver(swbm_);
	registerObserver(fightersManager_);
	registerObserver(life_);
	registerObserver(gameManager_);
	registerObserver(&soundManager_);
}

void ExampleGame::closeGame() {
	cs_->setMode(0);
	for (int i = 0; i < actors_.size(); i++)
	{
		if (actors_[i] != nullptr)
			delete actors_[i];
		actors_[i] = nullptr;
	}
}

void ExampleGame::start() {
	exit_ = false;
	keep_ = false;

	MessageId id = MessageId::ROUND_START;
	Message m(id);
	send(&m);

	while (!exit_ || keep_) {
		Uint32 startTime = SDL_GetTicks();
		handleInput(startTime);
		if (gameManager_->isRunning()) update(startTime);
		if (ship_->getLives() <= 0) exit_ = true;
		if (!exit_) render(startTime);
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void ExampleGame::stop() {
	exit_ = true;
}

void ExampleGame::handleInput(Uint32 time) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {
			exit_ = true;
		}

		int flags;
		MessageId id = MessageId::BADGE_ON;
		Message m(id);

		MessageId id4 = MessageId::ROUND_OVER;
		Message m4(id4);

		MessageId id5 = MessageId::ROUND_START;
		Message m5(id5);

		GoUpLifeBar m2(fightersManager_->getFighter());

		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			exit_ = true;
			break;
			// Pressing f to toggle fullscreen.
		case SDLK_f:
			flags = SDL_GetWindowFlags(window_);
			if (!(flags & SDL_WINDOW_FULLSCREEN)) {
				SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
			}
			break;
		case SDLK_g:
			flags = SDL_GetWindowFlags(window_);
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(window_, 0);
			}
			break;
		case SDLK_b:
			send(&m);
			break;
		case SDLK_l:
			send(&m2);
			break;
		case SDLK_y:
			if (keep_) {
				exit_ = false;
				keep_ = false;
				send(&m5);
			}
			break;
		case SDLK_n:
			if (keep_) {
				exit_ = true;
				keep_ = false;
				send(&m4);
			}
			break;
		}

		if (XboxController::Instance()->getNumControllers() > 0) {
			if (event.type == SDL_JOYBUTTONDOWN)
			{
				XboxController::Instance()->onJoystickButtonDown(event);

				if (XboxController::Instance()->getButtonState(0, 0)) //A button
				{
					if (keep_) {
						exit_ = false;
						keep_ = false;
						send(&m5);
					}
				}

				else if (XboxController::Instance()->getButtonState(0, 2)) //X button
				{
					send(&m2);
				}

				else if (XboxController::Instance()->getButtonState(0, 3)) //Y button
				{
					send(&m);
				}

				else if (XboxController::Instance()->getButtonState(0, 1)) //B button
				{
					if (keep_) {
						exit_ = true;
						keep_ = false;
						send(&m4);
					}
				}

				else if (XboxController::Instance()->getButtonState(0, 7)) //select button
				{
					gameManager_->setRunning(false);
				}

				XboxController::Instance()->onJoystickButtonUp(event);
				if (event.type == SDL_JOYBUTTONUP)
					XboxController::Instance()->onJoystickButtonUp(event);
			}

		}

		for (GameObject* o : actors_) {
			if (o->isActive())
				o->handleInput(time, event);
		}

		//to connect xbox controller
		XboxController::Instance()->getNumControllers();
		if (event.type == SDL_JOYDEVICEADDED && XboxController::Instance()->getNumControllers() == 0)
			XboxController::Instance()->insertController();
		else if (event.type == SDL_JOYDEVICEREMOVED && XboxController::Instance()->getNumControllers() > 0)
			XboxController::Instance()->removeController();
	}
}

void ExampleGame::update(Uint32 time) {

	int m = cs_->getMode();
	if (m == 0) {
		badget1_->setActive(true);
		badget2_->setActive(false);
		badget3_->setActive(false);
		badget4_->setActive(false);
		badget5_->setActive(false);
	}
	else if (m == 1) {
		badget1_->setActive(false);
		badget2_->setActive(true);
		badget3_->setActive(false);
		badget4_->setActive(false);
		badget5_->setActive(false);
	}
	else if (m == 2) {
		badget1_->setActive(false);
		badget2_->setActive(false);
		badget3_->setActive(true);
		badget4_->setActive(false);
		badget5_->setActive(false);
	}
	else if (m == 3) {
		badget1_->setActive(false);
		badget2_->setActive(false);
		badget3_->setActive(false);
		badget4_->setActive(true);
		badget5_->setActive(false);
	}
	else if (m == 4) {
		badget1_->setActive(false);
		badget2_->setActive(false);
		badget3_->setActive(false);
		badget4_->setActive(false);
		badget5_->setActive(true);
	}

	for (GameObject* o : actors_) {
		if (o->isActive())
			o->update(time);
	}
}

void ExampleGame::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x000000FF));
	SDL_RenderClear(getRenderer());

	for (GameObject* o : actors_) {
		if (o->isActive())
			o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

void ExampleGame::receive(Message* msg) {
	SDL_Rect rect RECT(0, 0, getWindowWidth(), getWindowHeight());
	Texture* victory = getResources()->getImageTexture(Resources::Victory);
	Texture* loose = getResources()->getImageTexture(Resources::Loose);

	switch (msg->id_) {
	case END_PARTY:
		exit_ = true;
		keep_ = true;
		SDL_RenderClear(getRenderer());

		if (fightersManager_->getFighter()->getLives() > 0) {
			victory->render(getRenderer(), rect);
		}
		else {
			loose->render(getRenderer(), rect);
		}

		SDL_RenderPresent(getRenderer());
		break;
	}
}