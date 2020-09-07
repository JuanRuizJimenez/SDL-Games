#pragma once
#include "PacManObject.h"
#include "Texture.h"

class GameCharacter : public PacManObject {
private:
	int posXini; int posYini; //posiciones iniciales
	int posX; int posY; //posiciones actuales
	int dirX; int dirY; //direcciones actuales
	int widthFrame; int heightFrame; //tamaños del frame
	int rowFrame; int colFrame; //posiciones del frame
	int scale;
	Texture* textPtr; //puntero a la textura del gc
public:
	GameCharacter(Game2p0* g, PlayState* p, Texture* t, int x, int y, int dx, int dy, int w, int h, int row, int col); //constructora
	virtual ~GameCharacter(); //destructora (vacia y virtual)
	virtual void render(); //metodo virtual para renderizar el gc
	virtual void loadFromFile(ifstream& lect); //metodo virtual para cargar el gc desde un archivo
	virtual void saveToFile(ofstream& esc); //metodo virtual para guardar el gc en un archivo
	//METODOS AUXILIARES
	int getPosX() { return posX; }; //para obtener la posicion del gc
	int getPosY() { return posY; };
	int getPosXIni() { return posXini; }; //para obtener la posicion del gc
	int getPosYIni() { return posYini; };
	void setPosX(int x) { posX = x; }; //para actualizar la posicion del gc
	void setPosY(int y) { posY = y; };
	void setPosXIni(int x) { posXini = x; }; //para actualizar la posicion inicial del gc
	void setPosYIni(int y) { posYini = y; };
	int getDirX() { return dirX; }; //para obtener la direccion del gc
	int getDirY() { return dirY; };
	void setDirX(int dx) { dirX = dx; }; //para actualizar la direccion del gc
	void setDirY(int dy) { dirY = dy; };
	int getRow() { return rowFrame; }; //para obtener la columna y la fila en la que se encuentra el frame en la imagen
	int getCol() { return colFrame; };
	void setRow(int r) { rowFrame = r; }; //para actualizar la columna y la fila en la que se encuentra el frame en la imagen
	void setCol(int c) { colFrame = c; };
	void setScale(int s) { scale = s; }; //para actualizar el tamaño del gc
	virtual void defaultIni(); //devuelve al gc a su posicion inicial
	virtual void death() { defaultIni(); }; //llama a la funcion que devuelve a su estado inicial el gc
};
