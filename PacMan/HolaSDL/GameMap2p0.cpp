#include "GameMap2p0.h"
#include "Game2p0.h"
#include "PlayState.h"
#include "PacmanError.h"

GameMap2p0::GameMap2p0(Texture* text1, Texture* text2, Texture* text3, Game2p0* g, PlayState* p)
	: PacManObject(g, p) 
{
	//Para poder hacer en gamemap su render
	textura = text1;
	texturaFood = text2;
	texturaVit = text3;
	scaleX = 1.5; scaleY = 1;

	//Sirve para controlar el tamaño máximo que debe tener el tablero para que no sobrepase la puntuación.
	if (scaleX < 1.5 || scaleY < 1) {
		scaleX = 1.5;
		scaleY = 1;
	}
}

GameMap2p0::~GameMap2p0()
{
	//borramos memoria dinamica
	if (cells != nullptr) {
		for (int i = 0; i < rows; i++)
			delete[]cells[i];
		delete[]cells;
	}
	cells = nullptr;
}

void GameMap2p0::render() {
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			//creamos un rectangulo destino a cada vuelta de bucle
			int DestCellW = W;
			int DestCellH = H;

			SDL_Rect destRect;

			destRect.x = i * DestCellW;
			destRect.y = j * DestCellH;
			destRect.w = DestCellW;
			destRect.h = DestCellH;

			if (cells[j][i] == Wall) {
				//Renderizamos textura del muro
				textura->renderFrame(destRect, 0, 0);
			}
			else if (cells[j][i] == Food) {
				//Renderizamos textura de la comida
				texturaFood->renderFrame(destRect, 0, 0);
			}
			else if (cells[j][i] == Vitamins) {
				//Renderizamos textura de la vitamina
				q = rand() % 3;
				p = rand() % 4;
				texturaVit->renderFrame(destRect, q, p);
			}
		}
	}
}

void GameMap2p0::loadFromFile(ifstream& lect) {
	//lo primero en leer seran las dimensiones
	try {
		lect >> rows;
		lect >> cols;
		if (rows <= 0 || cols <= 0)
			throw FileFormatError("Dimensiones del mapa incorrectas");
	}
	catch (FileFormatError& e) {
		e.showMessage();
	}
	Game2p0* g = getGame();
	//calculamos tamaños de los frames
	W = (g->getWinWidth() / cols) / scaleX;
	H = (g->getWinHeight() / rows) / scaleY;
	//creamos matriz dinamica
	cells = new MapCell*[rows];
	for (int i = 0; i < rows; i++) {
		cells[i] = new MapCell[cols];
	}
	//vamos rellenando la matriz dinamica
	int number = 0; //numero leido
	int food = 0; //contador de comida
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			try {
				lect >> number;
				if (number == 0)
					cells[i][j] = Empty;
				else if (number == 1)
					cells[i][j] = Wall;
				else if (number == 2) {
					cells[i][j] = Food;
					food++;
				}
				else if (number == 3)
					cells[i][j] = Vitamins;
				else {
					cells[i][j] = Empty;
					throw FileFormatError ("Leido dato incorrecto, puesto como casilla vacia");
				}
			}
			catch (FileFormatError& e){
				e.showMessage();
			}
		}
	}
	getPlay()->setFood(food); //llevamos la comida contada al juego
}

void GameMap2p0::saveToFile(ofstream& esc) {
	//lo primero en escribir seran las dimensiones
	esc << rows << " ";
	esc << cols << endl;
	Game2p0* g = getGame();

	//vamos recorriendo la matriz dinamica
	int number = 0; //numero leido
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (cells[i][j] == Empty)
				number = 0;
			else if (cells[i][j] == Wall)
				number = 1;
			else if (cells[i][j] == Food)
				number = 2;
			else if (cells[i][j] == Vitamins)
				number = 3;
			else
				number = 0;
			esc << number << " ";
		}
		esc << endl;
	}
}