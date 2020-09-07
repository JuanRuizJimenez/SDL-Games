#include "AcelerationInputComponent.h"
#include "XboxController.h"

AcelerationInputComponent::AcelerationInputComponent(SDL_Keycode acelerate, SDL_Keycode desacelerate, 
	double thrust, double maxVel, double aFactor, double dFactor) : 
	acelerate_(acelerate), desacelerate_(desacelerate),
	thrust_(thrust), maxVel_(maxVel), aFactor_(aFactor), dFactor_(dFactor)
{
}

AcelerationInputComponent::~AcelerationInputComponent()
{
}

void AcelerationInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event)
{
	double velX = o->getDirection().getX() * thrust_;
	double velY = o->getDirection().getY() * thrust_;

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == acelerate_) {
			thrust_ += aFactor_;
		}
		else if (event.key.keysym.sym == desacelerate_) {
			thrust_ -= dFactor_;
		}
	}

	else if (XboxController::Instance()->getNumControllers() > 0) {

		if (event.type == SDL_JOYAXISMOTION) {
			XboxController::Instance()->onJoystickAxisMove(event);

			if (XboxController::Instance()->yvalue(0, 1) < 0)
			{
				thrust_ += aFactor_;
			}
			else if (XboxController::Instance()->yvalue(0, 1) > 0)
			{
				thrust_ -= dFactor_;
			}
		}
	}

	if (thrust_ > maxVel_) thrust_ = maxVel_;
	if (thrust_ < 0) thrust_ = 0;

	Vector2D v(velX, velY);
	o->setVelocity(v);
}