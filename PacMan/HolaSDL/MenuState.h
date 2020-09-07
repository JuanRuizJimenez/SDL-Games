#pragma once
#include "GameState.h"
#include "Button.h"

class MenuState : public GameState{
private:

public:
	MenuState(Game2p0* g); //constructora
	~MenuState(); //destructora
	virtual void render(); //llama al render de gs
	virtual void update(); //llama al update de gs
	virtual bool handleEvent(SDL_Event& event); //llama al handle event de gs
	static void toGame(Game2p0* game); //definimos esta funcion (COMO ESTATICA) para pasarsela como parametro al boton, va al juego haciendo push
	static void toSavGame(Game2p0* game); //definimos esta funcion (COMO ESTATICA) para pasarsela como parametro al boton, va juego haciendo push y activando el flag de partida guardada
	static void exit(Game2p0* game) { game->exitApp(); }; //definimos esta funcion (COMO ESTATICA) para pasarsela como parametro al boton, sale de la app
};

