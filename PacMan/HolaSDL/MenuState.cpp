#include "MenuState.h"
#include "StateMachine.h"
#include "PlayState.h"

MenuState::MenuState(Game2p0* g) : GameState(g){
	Game2p0* gm = g;
	Texture* tx = g->getTexture(15);
	Texture* tx2 = g->getTexture(16);
	Texture* tx3 = g->getTexture(17);
	stage.push_back(new Button(toGame, gm, tx, 0, 1, 250, 200));
	stage.push_back(new Button(toSavGame, gm, tx2, 2, 1, 250, 200));
	stage.push_back(new Button(exit, gm, tx3, 4, 1, 250, 200));
}

MenuState::~MenuState()
{
}

void MenuState::render() {
	GameState::render();
}

void MenuState::update() {
	GameState::update();
}

bool MenuState::handleEvent(SDL_Event& event) {
	//cuando esto sea un boton gestionara su event solo y solo habra que poner GameState::handleEvent
	bool handledEvent = false;
	handledEvent = (GameState::handleEvent(event));
	return handledEvent;
}

void MenuState::toGame(Game2p0* game) {
	StateMachine* sm = game->getStateMachine();
	sm->pushState(new PlayState(game, false));
}

void MenuState::toSavGame(Game2p0* game) {
	StateMachine* sm = game->getStateMachine();
	sm->pushState(new PlayState(game, true));
}
