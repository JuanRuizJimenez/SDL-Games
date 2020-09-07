#include "Ghost2p0.h"
#include "Game2p0.h"
#include "PlayState.h"

Ghost2p0::Ghost2p0(Game2p0* g, PlayState* p, Texture* t, int x, int y, int dx, int dy, int w, int h, int row, int col)
	: GameCharacter(g, p, t, x, y, dx, dy, w, h, row, col)
{
	rowFrameIni = row;
	colFrameIni = col;
	vitamined = false;
	cont = 0;
}

Ghost2p0::~Ghost2p0()
{
}

void Ghost2p0::update() {
	checkState();
	posibleDirs();
	selectDir();//Escogemos una de las posibles direcciones de manera aleatoria
	actPos(); //actualizamos posicion
	getPlay()->compGhost();
}

void Ghost2p0::loadFromFile(ifstream& lect) {
	GameCharacter::loadFromFile(lect);
}

void Ghost2p0::saveToFile(ofstream& esc) {
	GameCharacter::saveToFile(esc);
	esc << " " << endl;
}

void Ghost2p0::checkState() {
	if (vitamined) cont++;
	if (cont > 35) {
		if (cont % 2 == 0) { setRow(0); setCol(12); }
		else { setRow(3); setCol(12); }
	}
	if (cont >= 48) {
		defaultText();
		cont = 0;
		vitamined = false;
	}
}

void Ghost2p0::posibleDirs() {
	listaPares l;
	PlayState* play = getPlay();
	int posX = getPosX();
	int posY = getPosY();
	int dirX = getDirX();
	int dirY = getDirY();

	if (dirY != -1) //para que no tome como posible darse la vuelta
		if (play->nextCell(this, 0, 1)) {
			l.x = 0; l.y = 1;
			directions.push_back(l);
		}
	if (dirY != 1)
		if (play->nextCell(this, 0, -1)) {
			l.x = 0; l.y = -1;
			directions.push_back(l);
		}
	if (dirX != -1)
		if (play->nextCell(this, 1, 0)) {
			l.x = 1; l.y = 0;
			directions.push_back(l);
		}
	if (dirX != 1)
		if (play->nextCell(this, -1, 0)) {
			l.x = -1; l.y = 0;
			directions.push_back(l);
		}
}

void Ghost2p0::selectDir() {
	int dirX = 0; int dirY = 0;
	int random = 0; //numero aleatorio
	if (directions.size() != 0) { //si no esta el vector vacio
		random = rand() % directions.size();
		dirX = directions[random].x;
		dirY = directions[random].y;
	}
	//Callejón sin salida, volvemos hacia atrás
	else {
		dirX = getDirX() * -1;
		dirY = getDirY() * -1;
	}
	setDirX(dirX);
	setDirY(dirY);
	directions.clear(); //limpiamos vector
}

void Ghost2p0::actPos() {
	PlayState* play = getPlay();
	int posX = getPosX();
	int posY = getPosY();
	int dirX = getDirX();
	int dirY = getDirY();

	//Movemos
	posX += dirX;
	posY += dirY;

	//Coprobamos si nos salimos o no, para hacer el toroide
	if (posX < 0)
		posX = play->getCols() - 1;
	else if (posX >= play->getCols())
		posX = 0;
	if (posY < 0)
		posY = play->getRows() - 1;
	else if (posY > play->getRows())
		posY = 0;

	setPosX(posX);
	setPosY(posY);
}

void Ghost2p0::defaultVitamined() {
	//devolvemos al fantasma a su posicion inicial y reseteamos atributos
	GameCharacter::death();
	vitamined = false;
	cont = 0; defaultText();
}

void Ghost2p0::death() { 
	defaultVitamined();
	//a parte sumamos puntos
	getPlay()->scoreFant(); 
}
