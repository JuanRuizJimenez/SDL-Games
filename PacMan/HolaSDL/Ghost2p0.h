#pragma once
#include "GameCharacter.h"
#include <vector>

class Ghost2p0: public GameCharacter{
private:
	int rowFrameIni; //posicion de la textura inicial
	int colFrameIni; //asi no la perdemos al cambiar a estado vitaminado
	bool vitamined; //indica si el fantasma esta vitaminado
	int cont; //contador que maneja la duracion del estado vitaminado

protected:
	struct listaPares { //para poder guardar la direccion como un par, para los fantasmas sera mas comodo asi
		int x, y;
	};
	vector <listaPares> directions; //vector de pares de direcciones, es protegido para que los fantasmas inteligentes tambien puedan acceder a el

public:
	Ghost2p0(Game2p0* g, PlayState* p, Texture* t, int x, int y, int dx, int dy, int w, int h, int row, int col); //constructora
	virtual ~Ghost2p0(); //destructora
	virtual void update(); //se encarga de actualizar la posicion del propio fantasma
	virtual void loadFromFile(ifstream& lect); //metodo virtual para cargar el fantasma desde un archivo
    virtual void saveToFile(ofstream& esc); //metodo virtual para guardar el fantasma en un archivo
	//METODOS AUXILIARES
	void checkState(); //comprueba el estado vitaminado del fantasma y actua en consecuencia
	void posibleDirs(); //comprueba las direcciones a las que se puede mover
	virtual void selectDir(); //selecciona una de las direcciones posibles, si hay mas de una lo hace aleatoriamente
	void actPos(); //hace efectiva la posicion a la que se va a mover el fantasma
	void actVitamin() { vitamined = true; setRow(0); setCol(12); cont = 0; }; //marca al fantasma como vitaminado
	bool getVitamin() { return vitamined; }; //pregunta si el fantasma esta vitaminado
	void defaultText() { setRow(rowFrameIni); setCol(colFrameIni); }; //devuelve la textura original del fantasma
	void defaultVitamined(); //reseteamos atributos y llevamos al fantasma a su posicion original
	virtual void death(); //llama al metodo anterior y ademas suma puntuacion
};

