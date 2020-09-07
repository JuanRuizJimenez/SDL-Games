#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include "PacMan2p0.h"
#include "Ghost2p0.h"
#include "SmartGhost2p0.h"
#include "GameMap2p0.h"
#include <vector>
#include <list>
//#include "StateMachine.h"

//para evitar inclusiones circulares
class StateMachine;
class PlayState;

class Game2p0
{
private:
	SDL_Window* WINDOW; //punteros de SDL
	SDL_Renderer* RENDERER;
	bool error; bool exit; //booleanos de control
	int winWidth, winHeight; //tamaños de pantalla
	int FRAME_RATE; //tiempo
	int tex; //contador de texturas
	Texture* TEXTURE[20]; //texturas del juego
	StateMachine* stateMachine; //maquina de estados

public:
	Game2p0(); //constructora
	~Game2p0(); //destructora
	void loadTexture(string filename, int rows, int cols); //se encarga de cargar las texturas y llamar a su constructora
	void render(); //recorre la lista de game characters y llama a sus metodos render
	void update(); //recorre la lista de game characters y llama a sus metodos update
	void handleEvents(); //gestiona todos los eventos del juego
	void begin(); //mete el estado menu y llama al run
	void run(); //bucle principal del juego
	//METODOS AUXILIARES
	Texture* getTexture(int t) { return TEXTURE[t]; }; //para que objetos como los botones accedan a su textura
	StateMachine* getStateMachine() { return stateMachine; }; //para poder gestionar estados accediendo a la maquina desde otras clases
	int getWinWidth() { return winWidth; }; //para conocer el tamaño de la ventana
	int getWinHeight() { return winHeight; };
	void cleanSreen() { SDL_RenderClear(RENDERER); }; //limpia pantalla
	void exitApp(); //sale de la aplicacion
};

