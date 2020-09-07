#pragma once
#include "GameObject.h"

typedef void CallBackOnClick(Game2p0* g); 
//definimos el tipo de funcion callback, es el tipo de la funcion que pasaremos como parametro al callback
//hay que pasarle un puntero al juego porque va a ser una funcion estatica y no puede acceder al atributo game

class Button : public GameObject{
private:
	//reesribimos estos atributos porque no hereda de game character que es el que los tiene de normal
	int posX, posY; //posiciones del boton
	int widthFrame, heightFrame; //tamaños del boton
	Texture* textPtr; //puntero a su textura

protected:
	CallBackOnClick* cboc; //funcion callback generica que se llamara cuando haya un click en el boton

public:
	Button(CallBackOnClick* cb, Game2p0* g, Texture* t, int x, int y, int w, int h); //constructora, pasamos la funcion como puntero
	virtual ~Button(); //destructora
	virtual void render(); //metodo render, como no hereda de game character habra que reescribirlo aqui
	virtual void update() {}; //update
	virtual bool handleEvent(SDL_Event& event); //manejo de evento, comprobara el click en su area
};

