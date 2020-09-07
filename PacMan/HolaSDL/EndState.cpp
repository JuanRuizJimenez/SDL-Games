#include "EndState.h"
#include "StateMachine.h"

EndState::EndState(Game2p0* g) : GameState (g) {
	Game2p0* gm = g;
	Texture* tx = g->getTexture(18);
	Texture* tx2 = g->getTexture(17);
	stage.push_back(new Button(toMenu, gm, tx, 1, 1, 250, 200));
	stage.push_back(new Button(exit, gm, tx2, 3, 1, 250, 200));
}

EndState::~EndState()
{
}

void EndState::render() {
	GameState::render();
}

void EndState::update() {
	GameState::update();
}

bool EndState::handleEvent(SDL_Event& event) {
	//cuando esto sea un boton gestionara su event solo y solo habra que poner GameState::handleEvent
	bool handledEvent = false;
	handledEvent = (GameState::handleEvent(event));
	return handledEvent;
}

void EndState::toMenu(Game2p0* game) {
	StateMachine* sm = game->getStateMachine();
	sm->popState();
	sm->popState();
}