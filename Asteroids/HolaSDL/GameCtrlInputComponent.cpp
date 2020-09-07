#include "GameCtrlInputComponent.h"
#include "GameManager.h"
#include "XboxController.h"

GameCtrlInputComponent::GameCtrlInputComponent() {
}

GameCtrlInputComponent::~GameCtrlInputComponent() {
}

void GameCtrlInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {

	GameManager* gm = static_cast<GameManager*>(o);

	if (event.type == SDL_KEYDOWN) {

		// if any key pressed while not running
		if (!gm->isRunning()) {
			gm->setRunning(true);
		}
	}
	if (XboxController::Instance()->getNumControllers() > 0) {
		if (event.type == SDL_JOYBUTTONDOWN)
		{
			gm->setRunning(true);
		}
	}
}
