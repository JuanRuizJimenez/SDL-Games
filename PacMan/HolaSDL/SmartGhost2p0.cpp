#include "SmartGhost2p0.h"
#include "Game2p0.h"
#include "PlayState.h"
#include "PacmanError.h"

SmartGhost2p0::SmartGhost2p0(Game2p0* g, PlayState* p, Texture* t, int x, int y, int dx, int dy, int w, int h, int row, int col)
	:Ghost2p0(g, p, t, x, y, dx, dy, w, h, row, col)
{
	age = 0;
	parent = false;
	adult = false;
	old = false;
	dead = false;
	children = 0;
	maxChildren = 1;
}


SmartGhost2p0::~SmartGhost2p0()
{
}

void SmartGhost2p0::update() {
	if (!dead) {
		if (!old) {
			checkState();
			posibleDirs();
			if (!getVitamin() && age >= 100) //inteligente solo a partir de la edad 100, mientras sea niño se movera random
				selectDir();//Escogemos una de las posibles direcciones de manera inteligente
			else
				Ghost2p0::selectDir();//Escogemos una de las posibles direcciones de forma random
			actPos(); //actualizamos posicion
			getPlay()->compGhost(); //realizamos las comprobaciones genericas de fantasma

			if (age < 100 && age >= 0) {
				setScale(2);
				age++;
			}
			else if (age < 200 && age >= 100) {
				adult = true;
				setScale(1);
				getPlay()->compSmartGhost(); //tambien habra que comprobar si se cruza con un fantasma inteligente y se reproduce
				age++;
			}
			else {
				actVitamin();
				old = true;
			}
		}
		else
			actVitamin();
	}
}

void SmartGhost2p0::loadFromFile(ifstream& lect) {
	GameCharacter::loadFromFile(lect);
	try {
		lect >> age;
		if (age < 0)
			throw FileFormatError("leido fantasma inteligente con vida negativa, aparecera como muerto");
	}
	catch (FileFormatError& e) {
		e.showMessage();
	}
}

void SmartGhost2p0::saveToFile(ofstream& esc) {
	GameCharacter::saveToFile(esc);
	esc << " " << age << endl;
}

void SmartGhost2p0::selectDir() {
	PlayState* play = getPlay();
	int dirX = getDirX(); int dirY = getDirY();
	int posX = getPosX(); int posY = getPosY();
	//posX += dirX; posY += dirY;
	int posXPac = play->getPosXPacman();
	int posYPac = play->getPosYPacman();
	int distanceX = posX - posXPac;
	if (distanceX < 0) distanceX = -distanceX;
	int distanceY = posY - posYPac;
	if (distanceY < 0) distanceY = -distanceY;

	if (directions.size() != 0) { //si no esta el vector vacio
		//bucle recorriendo las direcciones y viendo cual acerca mas al pacman
		for (int i = 0; i < directions.size(); i++) {
			dirX = directions[i].x;
			dirY = directions[i].y;
			posX = getPosX();
			posY = getPosY();
			posX += dirX;
			posY += dirY;
			int distanceXaux = posX - posXPac;
			if (distanceXaux < 0) distanceXaux = -distanceXaux;
			int distanceYaux = posY - posYPac;
			if (distanceYaux < 0) distanceYaux = -distanceYaux;
			if (distanceXaux < distanceX || distanceYaux < distanceY){
				listaPares l; l.x = dirX; l.y = dirY;
				directionsFav.push_back(l);
			}
		}
		if (directionsFav.size() != 0) {
			int random = rand() % directionsFav.size();
			dirX = directionsFav[random].x;
			dirY = directionsFav[random].y;
		}
	}
	//Callejón sin salida, volvemos hacia atrás
	else {
		dirX = getDirX() * -1;
		dirY = getDirY() * -1;
	}
	setDirX(dirX);
	setDirY(dirY);
	directions.clear(); //limpiamos vectores
	directionsFav.clear();
}

void SmartGhost2p0::addChild() {
	children++;
	if (children >= maxChildren)
		parent = true;
}
