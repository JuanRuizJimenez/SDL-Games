//PRACTICA REALIZADA POR JUAN RUIZ JIMENEZ Y JAVIER CORDERO CALVO
#include "SDL.h"
#include "SDL_image.h"
#include "Game2p0.h"

using namespace std;

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game2p0 juego;

	juego.begin();

	SDL_Quit();

	return (0);
}