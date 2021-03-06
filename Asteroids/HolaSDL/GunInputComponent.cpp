#include "GunInputComponent.h"
#include "messages.h"
#include <algorithm>
#include "XboxController.h"

GunInputComponent::GunInputComponent(SDL_Keycode shoot, Observer* bm, Observer* shootbar,
	Uint8 shotsPerInterval, Uint32 timeInterval) : shoot_(shoot), bm_(bm), shotsPerInterval_(shotsPerInterval), timeInterval_(timeInterval)
{
	shotsRealized_ = 0;
	t = clock();
	iniTimeInterval_ = timeInterval;

	registerObserver(bm);
	registerObserver(shootbar);
}

GunInputComponent::~GunInputComponent()
{
}

void GunInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event)
{
	secondsPassed = (clock() - t) / CLOCKS_PER_SEC;

	if (secondsPassed >= timeInterval_) {
		shotsRealized_ = 0;
		timeInterval_ += iniTimeInterval_;
		MessageId id = MessageId::RESTART_BAR;
		Message m(RESTART_BAR);
		send(&m);
	}

	if (event.type == SDL_KEYDOWN || event.type == SDL_JOYBUTTONDOWN) {
		bool buttoned = false;

		if (XboxController::Instance()->getNumControllers() > 0) {
			XboxController::Instance()->onJoystickButtonDown(event);
			buttoned = XboxController::Instance()->getButtonState(0, 5);
		}

		if (event.key.keysym.sym == shoot_ || buttoned) {
			shotsRealized_++;

			if (shotsRealized_ <= shotsPerInterval_) {

				Vector2D position = o->getPosition();
				double posX = position.getX();
				double posY = position.getY();
				Vector2D direction = o->getDirection();
				double dirX = direction.getX();
				double dirY = direction.getY();
				Vector2D velocity = o->getVelocity();
				double velX = velocity.getX();
				double velY = velocity.getY();
				double width = o->getWidth();
				double height = o->getHeight();

				double posIniX = posX + width / 2 + dirX * height / 2;
				double posIniY = posY + height / 2 + dirY * height / 2;
				Vector2D posIni(posIniX, posIniY);

				Vector2D bulletVel = direction * max(2 * velocity.magnitude(), 2.0);

				FighterIsShooting m(static_cast<Fighter*>(o), posIni, bulletVel);
				send(&m);

				GoDownBar m2(static_cast<Fighter*>(o), shotsRealized_, shotsPerInterval_);
				send(&m2);
			}
		}
	}
}