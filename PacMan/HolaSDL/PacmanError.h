#pragma once
#include <string>

using namespace std;

//clase base
class PacmanError : public logic_error {
protected:
	string message;
public:
	PacmanError(const string& m) : logic_error(m) { message = m; };
	~PacmanError() {};
	void showMessage() { cout << "Error generico: " + message << endl; };
};

//clase para errores de SDL
class SDLError : public PacmanError {
protected:
	string message;
public:
	SDLError(const string& m) : PacmanError(m) { message = m; };
	~SDLError() {};
	void showMessage() { cout << "Error de SDL: " + message << endl; };
};

//clase para errores a la hora de abrir archivo
class FileNotFoundError : public PacmanError {
protected:
	string message;
public:
	FileNotFoundError(const string& m) : PacmanError(m) { message = m; };
	~FileNotFoundError() {};
	void showMessage() { cout << "Error abriendo archivo: " + message << endl; };
};

//clase para errores leyendo archivo
class FileFormatError : public PacmanError {
protected:
	string message;
public:
	FileFormatError(const string& m) : PacmanError(m) { message = m; };
	~FileFormatError() {};
	void showMessage() { cout << "Error leyendo archivo: " + message << endl; };
};