#include "GameObject.h"
#include <list>
#include "Game2p0.h"

#pragma once
class GameState
{
protected:
	Game2p0* game; //puntero a juego
	list<GameObject*> stage; //lista de game objects del estado
	
public:
	GameState(Game2p0* g); //constructora
	virtual ~GameState(); //destructora
	virtual void render(); //llama al render de cada uno de los go de su lista
	virtual void update(); //llama al update de cada uno de los go de su lista
	virtual bool handleEvent(SDL_Event& event); //llama al he de cada uno de los go de su lista
};

