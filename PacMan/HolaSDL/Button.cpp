#include "Button.h"

Button::Button(CallBackOnClick* cb, Game2p0* g, Texture* t, int x, int y, int w, int h) : GameObject (g){
	cboc = cb;
	textPtr = t;
	posX = x; posY = y;
	widthFrame = w; heightFrame = h;
}


Button::~Button()
{
}

void Button::render() {
	//Determinamos destino (matriz)
	int DestCellW = widthFrame;
	int DestCellH = heightFrame;

	SDL_Rect destRect;
	destRect.x = posX * DestCellW;
	destRect.y = posY * DestCellH;
	destRect.w = DestCellW;
	destRect.h = DestCellH;

	//Renderizamos textura del gc
	textPtr->renderFrame(destRect, 0, 0);
}

bool Button::handleEvent(SDL_Event& event) {
	bool handledEvent = false;
	if (event.type == SDL_MOUSEBUTTONDOWN) { //si es evento de raton
		int x = 0;
		int y = 0;
		SDL_GetMouseState(&x, &y); //comprobamos donde se ha producido el click

		Game2p0* g = getGame();

		//si el click es dentro de las dimensiones del boton
		if (x > (posX*widthFrame) && x < ((posX*widthFrame) + widthFrame)
			&& y >(posY*heightFrame) && y < ((posY*heightFrame) + heightFrame)) {

			Game2p0* g = getGame();
			cboc(g); //llamamos a la funcion callback generica que hemos pasado como parametro a la constructora
			cout << "boton pulsado" << endl;
			handledEvent = true; //marcamos el evento como handleado
		}
	}

	return handledEvent;
}
