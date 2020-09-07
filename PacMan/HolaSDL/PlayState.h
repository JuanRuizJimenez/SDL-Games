#pragma once
#include "GameState.h"
#include "GameMap2p0.h"
#include "PacMan2p0.h"

class PlayState : public GameState{
private:
	int level; //nivel del juego
	int maxLevel; //nivel maximo del juego
	int food; //comida del nivel
	int score; //puntuacion de la partida
	int pacmanLifes; //vidas del pacman
	bool sav; bool eat; bool newLevel; bool failArchive; //booleanos de control
	string name, code; //nombre del jugador y codigo de guarda/carga
	//aunque los punteros a pacman y mapa esten ya en la lista de go "stage", tener estos punteros fuera facilita mucho las cosas
	GameMap2p0* mapa; //puntero a mapa
	PacMan2p0* pacman; //puntero a pacman

public:
	PlayState(Game2p0* g, bool s); //constructora 
	~PlayState(); //destructora
	virtual void render(); //llama al render de gs y a los propios de este estado
	virtual void update(); //llama al update de gs y gestiona el paso de nivel y la muerte del jugador
	virtual bool handleEvent(SDL_Event& event); //NO llama al handle event de gs, este metodo se reescribe con la funcionalidad
	//necesaria para este estado, gestionamos los eventos de salir, ir a pause o de pacman (unico go con eventos de este estado)
	void loadArchives(); //metodo para guardar los archivos en fichero
	void saveArchives(); //metodo para cargar los archivos de un fichero de partida guardada
	void checkCode(); //metodo para poner nombre a los archivos de carga/guardado
	//METODOS AUXILIARES
	void isNewLevel() { newLevel = true; }; //para saber si es un nivel nuevo
	int getRows() { return mapa->getRows(); }; //para obtener las dimensiones del mapa
	int getCols() { return mapa->getCols(); }; 
	int getPosXPacman() { return (pacman->getPosX()); }; //para obtener las posiciones del pacman
	int getPosYPacman() { return (pacman->getPosY()); };
	void setFood(int value) { this->food = value; }; //para actualizar la cantidad de comida del nivel en el momento de carga
	void isSavedParty() { sav = true; }; //para saber si la partida es cargada de fichero de guardado o no
	bool nextCell(GameCharacter* c, int dirx, int diry); //comprueba la siguiente casilla a la que se dirige un gc
	void compGeneric(); //realiza las comprobaciones genericas del los gc con el resto del entorno
	void compPacman(); //realiza las comprobaciones del pacman con el resto del entorno
	void compGhost(); //realiza las comprobaciones de los fantasmas con el resto del entorno
	void compSmartGhost(); //realiza las comprobaciones de los fantasmas inteligentes con el resto del entorno (aumplia el metodo anterior)
	void emptyCas(int i, int j); //cada vez que nos comemos un fantasma sumamos puntuacion
	void scoreFant() { score += 50; }; //renderiza en el hud la puntuacion actual
	void renderScore(); //renderiza en el hud la puntuacion actual
	void renderLifes(); //renderiza en el hud las vidas actuales
};

