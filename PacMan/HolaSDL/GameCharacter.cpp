#include "GameCharacter.h"
#include "PacmanError.h"

GameCharacter::GameCharacter(Game2p0* g, PlayState* p, Texture* t, int x, int y, int dx, int dy, int w, int h, int row, int col)
	: PacManObject(g, p)
{
	textPtr = t;
	posXini = x; posYini = y;
	posX = x; posY = y;
	dirX = dx; dirY = y;
	widthFrame = w; heightFrame = h;
	rowFrame = row; colFrame = col;
	scale = 1;
}

GameCharacter::~GameCharacter()
{
}

void GameCharacter::render() {
	//Determinamos destino (matriz)
	int DestCellW = widthFrame;
	int DestCellH = heightFrame;

	SDL_Rect destRect;
	destRect.x = posX * DestCellW;
	destRect.y = posY * DestCellH;
	destRect.w = DestCellW / scale;
	destRect.h = DestCellH / scale;

	//Renderizamos textura del gc
	textPtr->renderFrame(destRect, rowFrame, colFrame);
}

void GameCharacter::loadFromFile(ifstream& lect) {
	//leemos los parametros comunes de todos los gc en su correspondiente linea
	try {
		lect >> posY; //posiciones
		lect >> posX;
		if (posX < 0 || posY < 0)
			throw FileFormatError("posiciones del go incorrectas");
	}
	catch (FileFormatError& e){
		e.showMessage();
	}
	try {
		lect >> posYini; //posiciones iniciales
		lect >> posXini;
		if (posXini < 0 || posYini < 0)
			throw FileFormatError("posiciones iniciales del go incorrectas");
	}
	catch (FileFormatError& e) {
		e.showMessage();
	}
	lect >> dirX; //direcciones
	lect >> dirY;
}

void GameCharacter::saveToFile(ofstream& esc) {
	esc << posY << " ";
	esc << posX << " ";
	esc << posYini << " ";
	esc << posXini << " ";
	esc << dirX << " ";
	esc << dirY;
}

//METODOS AUXILIARES

void GameCharacter::defaultIni() {
	//reestablecemos las posiciones a su valor original y anulamos la direccion
	posX = posXini; posY = posYini;
	dirX = 0; dirY = 0;
}
