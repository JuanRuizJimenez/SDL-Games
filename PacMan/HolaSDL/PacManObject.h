#pragma once
#include "GameObject.h"
//#include "PlayState.h"

//para evitar inclusiones circulares
class PlayState;

class PacManObject : public GameObject {
private:
	PlayState* play; //puntero a playstate, para poder llamar a sus metodos auxiliares

public:
	PacManObject(Game2p0* g, PlayState* p); //constructora
	~PacManObject(); //destructora
	virtual void loadFromFile(ifstream& lect) = 0;
	virtual void saveToFile(ofstream& esc) = 0;
	PlayState* getPlay() { return play; };
};

