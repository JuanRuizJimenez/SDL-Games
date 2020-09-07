#include "AcelerationInputComponent2.h"
#include "XboxController.h"

AcelerationInputComponent2::AcelerationInputComponent2(SDL_Keycode acelerate, SDL_Keycode desacelerate,
	double thrust, double maxVel, double reductionfactor) :
	acelerate_(acelerate), desacelerate_(desacelerate),
	thrust_(thrust), maxVel_(maxVel), reductionFactor_(reductionfactor)
{
}

AcelerationInputComponent2::~AcelerationInputComponent2()
{
}

void AcelerationInputComponent2::handleInput(GameObject* o, Uint32 time, const SDL_Event& event)
{
	Vector2D velocity = o->getVelocity();
	double velX = velocity.getX(); 
	double velY = velocity.getY();

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == acelerate_) {
			velX = velX + o->getDirection().getX() * thrust_;
			velY = velY + o->getDirection().getY() * thrust_;
		}
		else if (event.key.keysym.sym == desacelerate_) {
			velX = velX * reductionFactor_;
			velY = velY * reductionFactor_;
		}
	}

	else if (XboxController::Instance()->getNumControllers() > 0) {

		if (event.type == SDL_JOYAXISMOTION) {
			XboxController::Instance()->onJoystickAxisMove(event);

			if (XboxController::Instance()->yvalue(0, 1) < 0)
			{
				velX = velX + o->getDirection().getX() * thrust_;
				velY = velY + o->getDirection().getY() * thrust_;
			}
			else if (XboxController::Instance()->yvalue(0, 1) > 0)
			{
				velX = velX * reductionFactor_;
				velY = velY * reductionFactor_;
			}
		}
	}

	if (velX > maxVel_) velX = maxVel_;
	if (velY < -maxVel_) velY = -maxVel_;
	if (velX < -maxVel_) velX = -maxVel_;
	if (velY > maxVel_) velY = maxVel_;

	if (velX <= 0.1 && velX >= 0.1) velX = 0;
	if (velY <= 0.1 && velY >= 0.1) velY = 0;

	Vector2D v(velX, velY);
	o->setVelocity(v);
}