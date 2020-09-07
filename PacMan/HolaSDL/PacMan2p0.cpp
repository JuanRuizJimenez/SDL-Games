#include "PacMan2p0.h"
#include "Game2p0.h"
#include "PlayState.h"

PacMan2p0::PacMan2p0(Game2p0* g, PlayState* p, Texture* t, int x, int y, int dx, int dy, int w, int h, int row, int col)
	: GameCharacter(g, p, t, x, y, dx, dy, w, h, row, col)
{
	NdirX = 0; NdirY = 0;
	control = 0; 
	waka = 0;
	buffer = false;
	death = false;
}

PacMan2p0::~PacMan2p0()
{
}

void PacMan2p0::update() {
	//calculamos una nueva direccion con el pad
	calcNewDir(NdirX, NdirY);
	//si nos podemos mover en la direccion del buffer lo hacemos
	if (buffer) {
		setDirX(NdirX);
		setDirY(NdirY);
	}
	//creamos variables nececesarias
	int posx = getPosX();
	int posy = getPosY();
	int dirx = getDirX();
	int diry = getDirY();
	//cambio de posiciones si nos salimos de rango
	PlayState* play = getPlay();
	if (play->nextCell(this, dirx, diry) || buffer) {
		posx += dirx;
		if (posx >= play->getCols())
			posx = 0;
		else if (posx < 0)
			posx = play->getCols() - 1;

		posy += diry;
		if (posy >= play->getRows())
			posy = 0;
		else if (posy < 0)
			posy = play->getRows() - 1;

		setPosX(posx);
		setPosY(posy);

		play->compPacman();
	}
}

void PacMan2p0 ::loadFromFile(ifstream& lect) {
	GameCharacter::loadFromFile(lect);
}

void PacMan2p0::saveToFile(ofstream& esc) {
	GameCharacter::saveToFile(esc);
	esc << " ";
}

bool PacMan2p0::handleEvent(SDL_Event& event) {
	if (event.key.keysym.sym == SDLK_UP) {
		changeControl(3);
		return true;
	}
	else if (event.key.keysym.sym == SDLK_DOWN) {
		changeControl(4);
		return true;
	}
	else if (event.key.keysym.sym == SDLK_RIGHT) {
		changeControl(2);
		return true;
	}
	else if (event.key.keysym.sym == SDLK_LEFT) {
		changeControl(1);
		return true;
	}
	else if (event.key.keysym.sym == SDLK_SPACE) {
		changeControl(0);
		return true;
	}
	else
		return false;
}

//METODOS AUXILIARES

void PacMan2p0::calcNewDir(int ndx, int ndy) {
	if (control == 0) //parado
		ndx = ndy = 0;
	else if (control == 1) { //hacia la izquierda
		ndx = -1; ndy = 0;
	}
	else if (control == 2) { //hacia la derecha
		ndx = 1; ndy = 0;
	}
	else if (control == 3) { //hacia arriba
		ndx = 0; ndy = -1;
	}
	else if (control == 4) { //hacia abajo
		ndx = 0; ndy = 1;
	}
	bool food = false; //booleano que indica si hay comida o no
					   //preguntamos si pacman se puede mover en la direccion que tiene en el buffer
					   //y si hay comida en dicha casilla

	PlayState* play = getPlay();
	if (play->nextCell(this, ndx, ndy)) { //si nos podemos mover nos podremos mover en la dir del buffer
		buffer = true;
		animation(ndx, ndy); //animamos en dicha direccion
		
		//si no morimos actualizamos el valor de la nueva direccion en la clase
		if (!death) {
			NdirX = ndx;
			NdirY = ndy;
		}

		//si morimos devolvemos a pacman a su posicion inicial
		else {
			death = false;
			defaultIni();
		}
	}
	else
		buffer = false;
}

void PacMan2p0::animation(int ndx, int ndy) {
	//elegiremos un sprite u otro en funcion de la animacion que vayamos a tomar
	//solo llegaremos a este metodo que cambia la direccion si podemos movernos en la 
	//direccion que tenemos

	//tenemos una variable waka que ira cambiando cada vuelta del bucle, cuya funcion sera
	//ir cambiando el sprite para que abra y cierre la boca
	int row = getRow();
	int col = getCol();
	if (ndx == 0 && ndy == 0) {
		if (waka == 0) {
			row = 0; col = 11; waka = 1;
		}
		else {
			row = 0; col = 10; waka = 0;
		}
	}
	else if (ndx == 0 && ndy == 1) {
		if (waka == 0) {
			row = 1; col = 11; waka = 1;
		}
		else {
			row = 1; col = 10; waka = 0;
		}
	}
	else if (ndx == 0 && ndy == -1) {
		if (waka == 0) {
			row = 3; col = 11; waka = 1;
		}
		else {
			row = 3; col = 10; waka = 0;
		}
	}
	else if (ndx == 1 && ndy == 0) {
		if (waka == 0) {
			row = 0; col = 11; waka = 1;
		}
		else {
			row = 0; col = 10; waka = 0;
		}
	}
	else if (ndx == -1 && ndy == 0) {
		if (waka == 0) {
			row = 2; col = 11; waka = 1;
		}
		else {
			row = 2; col = 10; waka = 0;
		}
	}
	setRow(row);
	setCol(col);
}

void PacMan2p0::defaultIni() {
	//devuelve a pacman a su posicion inicial y pone su dir a 0 y el frame equivalente a estar parado
	GameCharacter::defaultIni();
	NdirX = 0; NdirY = 0;
	setRow(0); setCol(11);
}
