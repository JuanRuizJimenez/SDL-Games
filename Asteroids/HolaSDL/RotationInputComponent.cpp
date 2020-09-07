#include "RotationInputComponent.h"
#include "XboxController.h"

RotationInputComponent::RotationInputComponent(SDL_Keycode clockwise, SDL_Keycode counterclockwise, double degrees) :
	clockwise_(clockwise), counterclockwise_(counterclockwise), degrees_(degrees)
{
}

RotationInputComponent::~RotationInputComponent()
{
}

void RotationInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) 
{
	Vector2D direction = o->getDirection();

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == clockwise_) {
			direction.rotate(degrees_);
		}
		else if (event.key.keysym.sym == counterclockwise_) {
			direction.rotate(-degrees_);
		}
	}

	else if (XboxController::Instance()->getNumControllers() > 0) {

		if (event.type == SDL_JOYAXISMOTION) {
			XboxController::Instance()->onJoystickAxisMove(event);

			if (XboxController::Instance()->xvalue(0, 2) > 0)
			{
				direction.rotate(degrees_/3);
			}
			else if (XboxController::Instance()->xvalue(0, 2) < 0)
			{
				direction.rotate(-degrees_/3);
			}
		}
	}

	o->setDirection(direction);
}