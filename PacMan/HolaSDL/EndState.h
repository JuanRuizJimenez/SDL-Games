#pragma once
#include "GameState.h"
#include "Button.h"

class EndState : public GameState{
private:

public:
	EndState(Game2p0* g); //constructora
	~EndState(); //destructora
	virtual void render(); //llama al render de game state
	virtual void update(); //llama al update de game state
	virtual bool handleEvent(SDL_Event& event); //llama al handle event del game state
	static void toMenu(Game2p0* game); //definimos esta funcion (COMO ESTATICA) para pasarsela como parametro al boton, va al menu haciendo pop
	static void exit(Game2p0* game) { game->exitApp(); }; //definimos esta funcion (COMO ESTATICA) para pasarsela como parametro al boton,sale de la app
};

