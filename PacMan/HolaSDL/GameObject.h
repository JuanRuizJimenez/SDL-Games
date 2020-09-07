#pragma once
#include "Texture.h"
//#include "Game2p0.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class Game2p0; //para evitar dependencias no lo incluimos si no que hacemos una clase vacia con el mismo nombre

class GameObject
{
private:
	Game2p0* gamePtr; //puntero a juego
public:
	GameObject(Game2p0* g); //constructora (vacia)
	virtual ~GameObject(); //destructora (vacia y virtual)
	virtual void render() = 0; //metodo abstracto para renderizar el go
	virtual void update() = 0; //metodo abstracto para actualizar la logica del go
	virtual bool handleEvent(SDL_Event& event) { return false; }; 
	//todo lo que herede de go hara un handleo de evento (un unico evento, el que le pasen)
	//METODOS AUXILIARES
	Game2p0* getGame() { return gamePtr; }; //metodo para poder acceder al juego desde os go
};

