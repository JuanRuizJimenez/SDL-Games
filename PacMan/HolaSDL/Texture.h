#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

class Texture
{
private:
	SDL_Texture* TEXTURE = nullptr; //Puntero a textura de sdl, se rellenara en el load
	SDL_Renderer* RENDERER = nullptr; //Puntero a renderer de sdl, se copiara de la clase Game
	string FILENAME; //Ruta del archivo
	int	W = 0;	
	int	H = 0; //Tama�os de la imagen completa
	int FW = 0;		
	int FH = 0;	//Tama�os de cada frame de la imagen


public:
	Texture(SDL_Renderer* renderer, string filename = " "); //Constructora
	~Texture(); //Destructora (llama a free)
	void load(int rows, int cols); //Carga una textura completa, habra que determinar el numero
								   //de filas y columnas de esta para poder determinar el tama�o de cada frame
	void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE);//Pinta un rectangulo fuente del tama�o
																			 //que sea por toda la pantalla
	void renderComplete();

	void renderFrame(SDL_Rect& destRect, 
		int row, int col, SDL_RendererFlip flip = SDL_FLIP_NONE);//Pinta en un destino concreto el frame concreto 
	                                                             //de una textura determinado por su fila y columna
	void free();//Libera memoria dinamica
};

