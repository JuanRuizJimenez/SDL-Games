#pragma once
#include "GameState.h"
#include "Button.h"

class PauseState : public GameState{
private:

public:
	PauseState(Game2p0* g); //constructora
	~PauseState(); //destructora
	virtual void render(); //llama al render de gs
	virtual void update(); //llama al update de gs
	virtual bool handleEvent(SDL_Event& event); //llama al he del gs
	static void resume(Game2p0* game); //definimos esta funcion (COMO ESTATICA) para pasarsela como parametro al boton, va al juego haciendo pop
	static void exit(Game2p0* game) { game->exitApp(); };//definimos esta funcion (COMO ESTATICA) para pasarsela como parametro al boton, sale de la app
	static void exitAndSave(Game2p0* game); //definimos esta funcion (COMO ESTATICA) para pasarsela como parametro al boton, sale de la app y guarda la partida
	static void toMenu(Game2p0* game); //definimos esta funcion (COMO ESTATICA) para pasarsela como parametro al boton, nos lleva al menu
};

