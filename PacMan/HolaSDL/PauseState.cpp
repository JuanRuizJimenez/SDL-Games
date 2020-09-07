#include "PauseState.h"
#include "StateMachine.h"
#include "PlayState.h"

PauseState::PauseState(Game2p0* g) : GameState(g){
	Game2p0* gm = g;
	Texture* tx = g->getTexture(15);
	Texture* tx2 = g->getTexture(19);
	Texture* tx3 = g->getTexture(18);
	stage.push_back(new Button (resume, gm, tx, 1, 1, 250, 200));
	stage.push_back(new Button(exitAndSave, gm, tx2, 2, 1, 250, 200));
	stage.push_back(new Button(toMenu, gm, tx3, 3, 1, 250, 200));
}


PauseState::~PauseState()
{
}

void PauseState::render() {
	GameState::render();
}

void PauseState::update() {
	GameState::update();
}

bool PauseState::handleEvent(SDL_Event& event) {
	//cuando esto sea un boton gestionara su event solo y solo habra que poner GameState::handleEvent
	bool handledEvent = false;
	handledEvent = (GameState::handleEvent(event));
	return handledEvent;
}

void PauseState::resume(Game2p0* game) {
	StateMachine* sm = game->getStateMachine();
	sm->popState();
}

void PauseState::exitAndSave(Game2p0* game) {
	StateMachine* sm = game->getStateMachine();
	//para poder guardar la partida vamos antes al menu de juego para poder llamar asi al metodo save, luego salimos
	sm->popState();
	GameState* state = sm->currentState();
	(static_cast<PlayState*>(state))->saveArchives();
	exit(game); //llamada a la funcion aqui definida (en el .h)
}

void PauseState::toMenu(Game2p0* game) {
	StateMachine* sm = game->getStateMachine();
	sm->popState();
	sm->popState();
}