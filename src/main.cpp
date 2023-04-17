// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>

#include "./game/Game.h"

#include "sdlutils/sdlutils_demo.h"

using namespace std;

int main(int ac, char **av) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try {
		Game* g = new Game(); // Crea el juego.
		g->run(); // Inicia bucle de juego.
		SDL_Delay(2000); // Delay antes de cerrar el juego.
		delete(g); // Elimina basura.
	} 
	catch (const std::string &e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	} 
	catch (const char *e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	} 
	catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	} 
	catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}
	return 0;
}

