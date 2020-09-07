#pragma once
#include "Ghost2p0.h"

class SmartGhost2p0 : public Ghost2p0 {
private:
	int age; //edad del fantasma que determinara su situacion
	int children; //numero de hijos que ha tenido
	int maxChildren; //numero maximo de hijos que puede tener
	bool parent; //se activa si el fantasma es padre y no puede tener mas hijos
	bool adult; //se activa si el fantasma es adulto
	bool old; //se activa si el fantasma es viejo
	bool dead; //se activa si el fantasma es comido por pacman
	vector <listaPares> directionsFav; //este vector de direcciones trabaja en paralelo al normal con la peculiaridad que aqui solo entraran direcciones que
									   //acerquen al fantasma inteligente al pacman
public:
	SmartGhost2p0(Game2p0* g, PlayState* p, Texture* t, int x, int y, int dx, int dy, int w, int h, int row, int col); //contructora
	virtual ~SmartGhost2p0(); //destructora
	virtual void update(); //se encarga de actualizar la posicion del fantasma pero esta vez de forma inteligente
	virtual void loadFromFile(ifstream& lect); //metodo virtual para cargar el fantasma desde un archivo
	virtual void saveToFile(ofstream& esc); //guarda en archivo
	virtual void selectDir(); //selecciona una direccion pero esta vez en funcion de la posicion del pacman
	bool getParent() { return parent; }; //para conocer el estado del fantasma inteligente
	bool getAdult() { return adult; }; //""
	bool getOld() { return old; }; //""
	bool getDead() { return dead; }; //""
	void addChild(); //se suma el numero de hijos que tiene
	void out(int x, int y) { setPosXIni(x); setPosYIni(y); dead = true; }; //para sacar al fantasma del gameplay
};

