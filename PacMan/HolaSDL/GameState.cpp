#include "GameState.h"

GameState::GameState(Game2p0* g){
	game = g;
}

GameState::~GameState(){
	//limpiamos memoria dinamica
	for (list<GameObject*>::iterator it = stage.begin();
		it != stage.end(); ++it) {
		if (*it != nullptr) {
			delete *it;
		}
	}
	stage.clear();
}

void GameState::render() {
	for (list<GameObject*>::iterator it = stage.begin();
		it != stage.end(); ++it) {
		(*it)->render();
	}
}

void GameState::update() {
	for (list<GameObject*>::iterator it = stage.begin();
		it != stage.end(); ++it) {
		(*it)->update();
	}
}

bool GameState::handleEvent(SDL_Event& event) {
	list<GameObject*>::iterator it = stage.begin();
	bool capturedEvent = false;
	bool handledEvent = false;
	//IMPORTANTE
	//puede haber algunos casos en los que si se ha hecho un evento, sea de los que cambian de estado
	//si cambiamos de estado y el bucle sigue, el programa dara errores
	//para evitarlos, si se detecta que el evento ha sido tratado, salimos del bucle inmediatamente y sin tocar el iterador
	//(no tiene sentido seguir gestionando eventos si ya ha sido tratado -> nos salimos)
	while (!capturedEvent && it != stage.end()) {
		capturedEvent = ((*it)->handleEvent(event));
		handledEvent = capturedEvent;
		if(!capturedEvent)++it;
	}
	if (event.type == SDL_QUIT) {
		game->exitApp();
		handledEvent = true;
	}
	return handledEvent;
}