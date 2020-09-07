#pragma once
#include "GameCharacter.h"

class PacMan2p0: public GameCharacter{
private:
	int NdirX; int NdirY; //nuevas direcciones que puede tener pacman
	int control; //variable de control para actualizar el objeto y lo que va a hacer: 0 = parado, 1 = mov izda, 2 = mov dcha, 3 = mov arriba, 4 = mov abajo
	int waka; //atributo cambiante entre 0 y 1 que hace a pacman abrir y cerrar la boca
	bool buffer; //indica si hacer activa la nueva direccion de pacman o no
	bool death; //indica si pacman muere

public:
	PacMan2p0(Game2p0* g, PlayState* p, Texture* t, int x, int y, int dx, int dy, int w, int h, int row, int col); //constructora
	~PacMan2p0(); //destructora (vacia y virtual)
	void update(); //se encarga de actualizar la posicion del propio pacman y comprueba los efectos de dicho desplazamiento
	virtual void loadFromFile(ifstream& lect); //metodo virtual para cargar el pacman desde un archivo
	virtual void saveToFile(ofstream& esc); //metodo virtual para guardar el pacman en un archivo
	virtual bool handleEvent(SDL_Event& event);
	//METODOS AUXILIARES
	void calcNewDir(int ndx, int ndy); //calcula en el buffer una nueva direccion, si es viable la aplica
	void animation(int ndx, int ndy); //animacion del pacman en funcion de como se mueva
	void defaultIni(); //metodo virtual para poder colocar a pacman en su posicion inicial (amplia el de gc)
	void setDeath() { death = true; }; //para marcar pacman como muerto
	virtual void changeControl(int value) { control = value; }; //se encarga de poder cambiar la variable control desde handleEvents
};

