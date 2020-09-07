#include "PlayState.h"
#include "StateMachine.h"
#include "PauseState.h"
#include "EndState.h"
#include "PacmanError.h"

PlayState::PlayState(Game2p0* g, bool s) : GameState (g)
{
	level = 0; maxLevel = 2; food = 0;
	score = 0; pacmanLifes = 3;
	code = ""; name = "Juan";
	sav = s; eat = false; newLevel = true; failArchive = false;
	mapa = nullptr; pacman = nullptr; 
}

PlayState::~PlayState(){
}

void PlayState::render() {
	GameState::render();
	renderScore();
	renderLifes();
}

void PlayState::update() {
	GameState::update();
	if (newLevel) {
		level++;
		loadArchives();
		newLevel = false;
	}
	if (pacmanLifes <= 0) {
		game->getTexture(8)->renderComplete();
		SDL_Delay(1000);
		StateMachine* sm = game->getStateMachine();
		sm->pushState(new EndState(game));
	}
	if (food == 0) { //si terminamos la comida del nivel
		game->cleanSreen();//limpiamos pantalla
		if (!failArchive) game->getTexture(7)->renderComplete();//textura de victoria
		else failArchive = false;
		SDL_Delay(1000);
		if (!sav) {
			if (level < maxLevel)
				newLevel = true;
			else {
				StateMachine* sm = game->getStateMachine();
				sm->pushState(new EndState(game));
			}
		}
		else {
			StateMachine* sm = game->getStateMachine();
			sm->pushState(new EndState(game));
		}
	}
}

bool PlayState::handleEvent(SDL_Event& event) {
	bool handledEvent = false;
	if (event.type == SDL_QUIT) {
		game->exitApp();
		handledEvent = true;
	}
	else if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			StateMachine* sm = game->getStateMachine();
			sm->pushState(new PauseState(game));
			handledEvent = true;
		}
		else {
			pacman->handleEvent(event);
			handledEvent = true;
		}
	}
	return handledEvent;
}

void PlayState::checkCode() {
	game->cleanSreen();
	code = ""; //codigo vacio
	game->getTexture(12)->renderComplete();
	int numbr = -1;
	bool error = false;
	bool exitCode = false;
	while (!error && !exitCode) {
		SDL_Event event;
		while (SDL_PollEvent(&event) && !exitCode && !error) {
			error = false;
			if (event.type == SDL_QUIT) {
				exitCode = true;
				game->exitApp();
			}
			//iremos esperando la entrada de numeros y quedandonos con su valor
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_0) {
					numbr = 0;
				}
				else if (event.key.keysym.sym == SDLK_1) {
					numbr = 1;
				}
				else if (event.key.keysym.sym == SDLK_2) {
					numbr = 2;
				}
				else if (event.key.keysym.sym == SDLK_3) {
					numbr = 3;
				}
				else if (event.key.keysym.sym == SDLK_4) {
					numbr = 4;
				}
				else if (event.key.keysym.sym == SDLK_5) {
					numbr = 5;
				}
				else if (event.key.keysym.sym == SDLK_6) {
					numbr = 6;
				}
				else if (event.key.keysym.sym == SDLK_7) {
					numbr = 7;
				}
				else if (event.key.keysym.sym == SDLK_8) {
					numbr = 8;
				}
				else if (event.key.keysym.sym == SDLK_9) {
					numbr = 9;
				}
				else if (event.key.keysym.sym == SDLK_RETURN) {
					//cuando se pulsa enter acaba 
					exitCode = true;
				}
				else { //si no mete numero activamos flag de error
					error = true;
				}
				if (!error && !exitCode) {
					//añadimos el numero a la cadena de texto
					code = code + to_string(numbr);
				}
			}
		}
	}
}

void PlayState::loadArchives() { //CAMBIAR PUNTERO A GAME POR PUNTERO A PLAYSTATE
	ifstream lecture;
	try {
		if (!sav) //si no es partida guardada
			lecture.open("level0" + to_string(level) + ".pac");
		else { //si es partida guardada
			checkCode(); //pedimos el codigo de la partida
			lecture.open(code + ".pac");
		}
		if (lecture.fail()) {
			throw FileNotFoundError("El archivo que querias abrir no existe");
		}
	}
	catch (FileNotFoundError& e) {
		e.showMessage();
		lecture.open("level01.pac"); //con esto conseguimos ir a la pantalla de fin
		failArchive = true;
	}
	
		if (sav) {  //solo cargaremos esto si es partida guardada
			lecture >> name;
			lecture >> level;
		}

		//ahora iremos creando los objetos del juego
		for (list<GameObject*>::iterator it = stage.begin();
			it != stage.end(); ++it) {
			if (*it != nullptr) delete *it;
		}
		stage.clear();

		//if (mapa != nullptr) delete mapa;
		GameObject* aux3;
		aux3 = new GameMap2p0(game->getTexture(2), game->getTexture(3), game->getTexture(4), game, this);
		dynamic_cast<PacManObject*>(aux3)->loadFromFile(lecture);
		if (dynamic_cast<GameMap2p0*>(aux3))
			mapa = dynamic_cast<GameMap2p0*>(aux3);

		int w = mapa->getFrameWidth();
		int h = mapa->getFrameHeight();

		GameObject* aux2;
		aux2 = new PacMan2p0(game, this, game->getTexture(1), 0, 0, 0, 0, w, h, 0, 11);
		//de momento solo metemos al pacman en la posicion pero la informacion no se leera
		//hasta despues de leer los fantasmas para seguir el orden logico
		stage.push_back(aux2);
		stage.push_back(aux3);

		int frame = 0;
		int fantNum = 0;
		lecture >> fantNum;
		for (int a = 0; a < fantNum; a++) {
			GameObject* aux;
			int smart = 0;
			lecture >> smart;
			if (smart == 0) {
				aux = new Ghost2p0(game, this, game->getTexture(1), 0, 0, 0, 0, w, h, 0, frame);
				frame += 2;
			}
			else
				aux = new SmartGhost2p0(game, this, game->getTexture(1), 0, 0, 0, 0, w, h, 0, 8);
			dynamic_cast<PacManObject*>(aux)->loadFromFile(lecture);
			stage.push_back(aux);
		}

		dynamic_cast<PacManObject*>(aux2)->loadFromFile(lecture);
		if (dynamic_cast<PacMan2p0*>(aux2))
			pacman = dynamic_cast<PacMan2p0*>(aux2);

		if (sav) {
			lecture >> score;
			lecture >> pacmanLifes;
		}

		lecture.close();
}

void PlayState::saveArchives() {
	checkCode(); //pedimos el codigo con el que se guardara 
	ofstream escriture;
	escriture.open(code + ".pac");
	if (!escriture.fail()) {
		//vamos guardando los datos relevantes de la partida
		escriture << name << " " << level << endl;
		mapa->saveToFile(escriture);
		int numberOfGhosts = 0;
		for (list<GameObject*>::iterator it = stage.begin();
			it != stage.end(); ++it) {
			if (dynamic_cast<SmartGhost2p0*>((*it)) != nullptr) {
				if (!(dynamic_cast<SmartGhost2p0*>(*it)->getDead())) {
					numberOfGhosts++;
				}
			}
			else if (dynamic_cast<Ghost2p0*>((*it)) != nullptr) {
				numberOfGhosts++;
			}
		}
		//indicamos el numero de fantasmas
		escriture << numberOfGhosts << endl;
		for (list<GameObject*>::iterator it = stage.begin();
			it != stage.end(); ++it) {
			if (dynamic_cast<SmartGhost2p0*>((*it)) != nullptr) {
				if (!(dynamic_cast<SmartGhost2p0*>(*it)->getDead())) {
					escriture << "1" << " ";
					dynamic_cast<PacManObject*>((*it))->saveToFile(escriture);
				}
			}
			else if (dynamic_cast<Ghost2p0*>((*it)) != nullptr) {
				escriture << "0" << " ";
				dynamic_cast<PacManObject*>((*it))->saveToFile(escriture);
			}
		}
		//lo ultimo en guardar sera el pacman y la informacion de juego 
		pacman->saveToFile(escriture);
		escriture << score << " ";
		escriture << pacmanLifes;

		escriture.close();
	}
	else { cout << "Error guardando los archivos"; throw std::domain_error("Error guardando los archivos"); }
}

bool PlayState::nextCell(GameCharacter* c, int dirx, int diry) {
	//Comprobamos si nos salimos dle mapa
	int x = c->getPosX() + dirx;
	int y = c->getPosY() + diry;
	int rows = mapa->getRows();
	int cols = mapa->getCols();
	if (x >= cols)
		x = 0;
	else if (x < 0)
		x = cols - 1;
	if (y >= rows)
		y = 0;
	else if (y < 0)
		y = rows - 1;

	return (mapa->cells[y][x] != mapa->Wall);
}

void PlayState::compGeneric() {
	//comprobacion generica de los gc
	for (list<GameObject*>::iterator it = stage.begin();
		it != stage.end(); ++it) {
		if (dynamic_cast<Ghost2p0*>(*it) != nullptr) {
			if (((dynamic_cast<GameCharacter*>(*it))->getPosX() == pacman->getPosX() 
				&& (dynamic_cast<GameCharacter*>(*it))->getPosY() == pacman->getPosY()))
			{
				if (dynamic_cast<Ghost2p0*>((*it))->getVitamin()) { //si es un fantasma vitaminado y ademas inteligente lo sacamos del gameplay
					if (dynamic_cast<SmartGhost2p0*>((*it)) != nullptr) {
						dynamic_cast<SmartGhost2p0*>(*it)->out((1280 / mapa->getFrameWidth()) + 1, 0); //PONER WINWIDTH
					}
					dynamic_cast<Ghost2p0*>(*it)->death();
				}
				else {
					pacmanLifes--; //quitamos vida
					for (list<GameObject*>::iterator it2 = stage.begin();
						it2 != stage.end(); ++it2)
						if (dynamic_cast<Ghost2p0*>(*it2) != nullptr) {
							dynamic_cast<Ghost2p0*>(*it2)->defaultVitamined(); //estado original
						}
					pacman->defaultIni(); //estado original
					SDL_Delay(300);
				}
			}
		}
	}
}

void PlayState::compPacman() {
	int x = pacman->getPosX();
	int y = pacman->getPosY();
	//comprobamos si hay comida
	bool c;
	if ((mapa->cells[y][x] == mapa->Food)) {
		c = true;
		eat = true;
	}
	//comprobamos si hay vitamina
	else if (mapa->cells[y][x] == mapa->Vitamins) {
		c = true;
		eat = false;
		for (list<GameObject*>::iterator it = stage.begin();
			it != stage.end(); ++it) {
			if (dynamic_cast<Ghost2p0*>(*it) != nullptr) {
				dynamic_cast<Ghost2p0*>(*it)->actVitamin();
			}
		}
	}
	else {
		c = false;
		eat = false;
	}

	compGeneric();

	if (c) emptyCas(x, y);
}

void PlayState::compGhost() {
	compGeneric();
}

void PlayState::compSmartGhost() {
	int bottom = 0;
	int top = stage.size();
	for (list<GameObject*>::iterator it = stage.begin();
		((it != stage.end()) && bottom < top); ++it) {
		if (dynamic_cast<SmartGhost2p0*>(*it) != nullptr) { //tenemos que encontrar un smart ghost en la lista
			for (list<GameObject*>::iterator it2 = stage.begin();
				it2 != stage.end(); ++it2) {
				GameCharacter* aux1 = dynamic_cast<GameCharacter*>(*it);
				GameCharacter* aux2 = dynamic_cast<GameCharacter*>(*it2);
				if (dynamic_cast<SmartGhost2p0*>(*it2) != nullptr && //tenemos que comprobar que el segundo elto es un smart ghost tambien y que no es el primero
					((aux2)->getPosXIni() != (aux1)->getPosXIni() || (aux2)->getPosYIni() != (aux1)->getPosYIni())) { //para saber que son distintos comprobamos que sus posiciones iniciales sean distintas

					if (((aux1)->getPosX() == (aux2)->getPosX() && (aux1)->getPosY() == (aux2)->getPosY()) //si coincide en posicion
						&& (dynamic_cast<SmartGhost2p0*>(*it)->getAdult()) && (dynamic_cast<SmartGhost2p0*>(*it2)->getAdult()) //si es adulto
						&& !(dynamic_cast<SmartGhost2p0*>(*it)->getOld()) && !(dynamic_cast<SmartGhost2p0*>(*it2)->getOld())) { //si no es viejo
						bool respawnNew = false;
						int respawnX = 0; int respawnY = 0;
						//int respawnDirX = 0; int respawnDirY = 0;
						for (int i = 0; i < 2; i++) {
							for (int j = 0; j < 2; j++) {
								if (nextCell((aux1), i, j)) {
									//vemos en que casilla se puede colocar el hijo
									respawnNew = true;
									respawnX = (aux1)->getPosX() + i;
									respawnY = (aux1)->getPosY() + j;
								}
							}
						}
						//si alguno de los dos no ha sido padre ya puede aparecer el hijo
						if (respawnNew && (!(dynamic_cast<SmartGhost2p0*>(*it)->getParent()) || !(dynamic_cast<SmartGhost2p0*>(*it2)->getParent()))) {
							dynamic_cast<SmartGhost2p0*>(*it)->addChild(); //sumamos hijo
							dynamic_cast<SmartGhost2p0*>(*it2)->addChild();
							int w = mapa->getFrameWidth();
							int h = mapa->getFrameHeight();
							GameCharacter* aux;
							aux = new SmartGhost2p0(game, this, game->getTexture(1), respawnX, respawnY, 0, 0, w, h, 0, 8);
							stage.push_back(aux);
						}
					}
				}
			}
		}
		bottom++;
	}
}

void PlayState::emptyCas(int i, int j) {
	mapa->cells[j][i] = mapa->Empty;
	if (eat) {
		food--;
		score = score + 10;
		cout << food << endl;
	}
}

void PlayState::renderScore() {
	//pintamos los puntos de la partida en pantalla
	//la posicion de los rectangulos destino dependera del tamaño de pantalla
	float offsetXScore = 1.21;
	float offsetYScore = 0;
	float offsetWScore = 8;
	float offsetHScore = 4;
	float offsetXNum = 1.1;
	float offsetYNum = 5;
	float offsetWNum = 30;
	float offsetHNum = 20;
	int winWidth = game->getWinWidth();
	int winHeight = game->getWinHeight();

	float plusOffset = 0.05;

	SDL_Rect destRectScore;
	destRectScore.x = winWidth / offsetXScore;
	destRectScore.y = 0;
	destRectScore.w = winWidth / 8;
	destRectScore.h = winHeight / 4;

	SDL_Rect destRectNum;
	destRectNum.x = winWidth / offsetXNum;
	destRectNum.y = winHeight / offsetYNum;
	destRectNum.w = winWidth / offsetWNum;
	destRectNum.h = winHeight / offsetHNum;

	//copia del valor para no machacarlo
	int p = score;

	//pintamos marco score
	game->getTexture(9)->renderFrame(destRectScore, 0, 0);

	//la textura de numeros (6) consta de los numeros 0 a 9 en horizontal
	//1 fila 10 columnas
	while (p > 0) {
		int a = p % 10; //el numero que queremos pintar (en orden de primero unidades, luego decenas...) 
						//sera el resto de la punt entre 10
		p = p / 10;
		game->getTexture(6)->renderFrame(destRectNum, 0, a);
		offsetXNum = offsetXNum + plusOffset;
		destRectNum.x = winWidth / offsetXNum;
	}
}

void PlayState::renderLifes() {
	//pintamos las vidas del pacman en pantalla
	float offsetXLifes = 1.1;
	float offsetYLifes = 2;
	float offsetWLifes = 30;
	float offsetHLifes = 20;
	int winWidth = game->getWinWidth();
	int winHeight = game->getWinHeight();

	float plusOffset = 0.05;

	SDL_Rect destRectLifes;
	destRectLifes.x = winWidth / offsetXLifes;
	destRectLifes.y = winHeight / offsetYLifes;
	destRectLifes.w = winWidth / offsetWLifes;
	destRectLifes.h = winHeight / offsetHLifes;

	SDL_Rect destRectHeart;
	destRectHeart.x = winWidth / offsetXLifes;
	destRectHeart.y = winHeight / (offsetYLifes + 1);
	destRectHeart.w = winWidth / offsetWLifes;
	destRectHeart.h = winHeight / offsetHLifes;

	for (int i = 0; i < pacmanLifes; i++) {
		game->getTexture(1)->renderFrame(destRectLifes, 0, 11);
		game->getTexture(10)->renderFrame(destRectHeart, 0, 0);
		offsetXLifes = offsetXLifes + plusOffset;
		destRectLifes.x = winWidth / offsetXLifes;
		destRectHeart.x = winWidth / offsetXLifes;
	}
}
