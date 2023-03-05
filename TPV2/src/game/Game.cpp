#include "Game.h"

Game::Game() {
	initSDL();// incio de SDL
	renderer = SDLUtils::instance()->renderer();// renderer
	window = SDLUtils::instance()->window();// ventana

	GameStateMachine::instance()->pushState(new PlayState());// comienza el juego en el playState
	exit = false;// salida de juego a false

}

void Game::initSDL() {
	SDLUtils::instance(); // Crea la instancia de SDLUtils
}


Game::~Game(){ // destructora
	SDL_DestroyRenderer(renderer);// detruye el renderer
	SDL_DestroyWindow(window);// destruye la ventana
	SDL_Quit();// sale del juego
}

void Game::run(){ // bucle de juego
	InputHandler::instance()->refresh();// actualiza el input
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {// bucle principal
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			GameStateMachine::instance()->clearStates(); // elimina estados
			startTime = SDL_GetTicks();
		}
		if (!exit) {
			render();
		}	
	}
}

void Game::update(){
	GameStateMachine::instance()->update();// update de la máquina de estados
}

void Game::render() { // Dibuja en pantalla el estado actual del juego
	SDL_RenderClear(renderer);
	GameStateMachine::instance()->render();
	SDL_RenderPresent(renderer); 
}

