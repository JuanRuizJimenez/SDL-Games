#include "Game2p0.h"
#include<stdlib.h>
#include<time.h>
#include <fstream>
#include <math.h>
#include "StateMachine.h"
#include "PlayState.h"
#include "MenuState.h"
#include "PacmanError.h"

Game2p0::Game2p0()
{
	//La ventana y el renderer los tendremos que crear desde el constructor del juego
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;
	winWidth = 1280;
	winHeight = 720;

	SDL_Init(SDL_INIT_EVERYTHING);
	WINDOW = SDL_CreateWindow("PacMan", winX, winY,
		winWidth, winHeight, SDL_WINDOW_SHOWN);
	RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
	if (WINDOW == nullptr || RENDERER == nullptr)
		cout << "Error initializing SDL\n";

	srand(time(nullptr));//semilla de aleatorios

	//Creamos maquina de estados
	stateMachine = new StateMachine();
						 
	//Cargamos las texturas
	tex = 0;
	loadTexture("..\\images\\fondoPM.png", 1, 1);
	loadTexture("..\\images\\characters1.png", 4, 14);
	loadTexture("..\\images\\wall.png", 1, 1);
	loadTexture("..\\images\\food2.png", 1, 1);
	loadTexture("..\\images\\fruit.png", 3, 4);
	loadTexture("..\\images\\title.png", 1, 1);
	loadTexture("..\\images\\numbers.png", 1, 10);
	loadTexture("..\\images\\win.png", 1, 1);
	loadTexture("..\\images\\lose.png", 1, 1);
	loadTexture("..\\images\\score.png", 1, 1);
	loadTexture("..\\images\\life.png", 1, 1);
	loadTexture("..\\images\\power.png", 1, 1);
	loadTexture("..\\images\\keyboard.png", 1, 1);
	loadTexture("..\\images\\menu.png", 1, 1);
	loadTexture("..\\images\\resume.png", 1, 1);
	loadTexture("..\\images\\play.png", 1, 1);
	loadTexture("..\\images\\load.png", 1, 1);
	loadTexture("..\\images\\exit.png", 1, 1);
	loadTexture("..\\images\\menub.png", 1, 1);
	loadTexture("..\\images\\save.png", 1, 1);

	//Pintamos titulo
	TEXTURE[5]->renderComplete();
	SDL_Delay(3000);


	//inicializamos booleanos de control
	exit = false; error = false;

	FRAME_RATE = 130; 
}

Game2p0::~Game2p0(){
	//borramos memoria dinamica
	for (int i = 0; i < tex; i++){
		delete TEXTURE[i];
		TEXTURE[i] = nullptr;
	}
	delete stateMachine;
}

void Game2p0::loadTexture(string filename, int rows, int cols) {
	//creo esta variable (text) para cada vez que carguemos una textura, 
	//se guarde en la siguiente posición del array al que corresponde
	if (filename == " ") {
		throw SDLError("Error cargando la textura");
	}
	else {
		//Recordamos que tenemos que guardar la textura en un array en una posición determinada del mismo
		try {
			TEXTURE[tex] = new Texture(RENDERER, filename);
			TEXTURE[tex]->load(rows, cols);
			tex++;
		}
		catch (SDLError& e) {
			e.showMessage();
		}
	}
}

void Game2p0::render() {
	//renderizamos los objetos
	SDL_RenderClear(RENDERER);
	stateMachine->currentState()->render();
	if(!exit) SDL_RenderPresent(RENDERER);
}

void Game2p0::update() {
	stateMachine->currentState()->update();
}

void Game2p0::handleEvents() {
	SDL_Event event;
	bool capturedEvent = false;
	//en cuanto capturemos un evento, salimos, asi evitamos fallos cuando cambiemos de estado
	//porque en cuanto cambiemos se dejaran de gestionar mas eventos
	while (SDL_PollEvent(&event) && !exit && !capturedEvent) {
		capturedEvent = (stateMachine->currentState()->handleEvent(event));
	}
}

void Game2p0::begin() {
	GameState* aux = new MenuState(this);
	stateMachine->pushState(aux);
	run();
}

void Game2p0::run() {
	int startime, frametime;
	while (!exit && !error) {
		//flujo natural de bucle
		startime = SDL_GetTicks();
		handleEvents();
		update();
		render();
		frametime = SDL_GetTicks() - startime;
		if (frametime < FRAME_RATE)SDL_Delay(FRAME_RATE - frametime);
	}
	stateMachine->clearStack(); //en cuanto salgamos de la app, limpiamos la maquina de estados (vaciamos la pila y su memoria dinamica)
}

void Game2p0::exitApp() {
	exit = true; 
}



