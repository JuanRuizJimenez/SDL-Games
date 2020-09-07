#pragma once
#include "PacManObject.h"
#include "Texture.h"

class Game2p0;
class PlayState;
class GameMap2p0: public PacManObject{
	friend class Game2p0; friend class PlayState;

private:
	int rows;//filas del mapa
	int cols;//columnas del mapa
	int W, H;//tamaño de casilla
	Texture* textura;//puntero a la textura del muro
	Texture* texturaFood;//puntero a la textura de la comida
	Texture* texturaVit;//puntero a la textura de la vitamina
	enum MapCell { Empty, Wall, Food, Vitamins }; //cada casilla sera de este tipo enumerado
	MapCell** cells;//matriz dinamica de casillas
	int q, p; //numeros aleatorios para cargar un frame aleatorio de la textura de vitaminas
	float scaleX; //escalado de la pantalla de juego
	float scaleY;
public:
	GameMap2p0(Texture* text1, Texture* text2, Texture* text3, Game2p0* g, PlayState* p);//constructora con parametros
	virtual ~GameMap2p0(); //destructora (limpia matriz dinamica)
	virtual void render(); //pinta el mapa
	virtual void update() {}; //actualiza el estado
	virtual void loadFromFile(ifstream& lect); //se carga sus datos desde archivo
	virtual void saveToFile(ofstream& esc);
	MapCell getCasilla(int i, int j) { return cells[i][j]; }; //devuelve el tipo de una casilla especifica
	int getFrameWidth() { return W; }; //para obtener el tamaño del frame de la casilla
	int getFrameHeight() { return H; };
	int getRows() { return rows; }; //para obtener las dimensiones del mapa
	int getCols() { return cols; };
};

