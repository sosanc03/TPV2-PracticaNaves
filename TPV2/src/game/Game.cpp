#include "Game.h"

Game::Game() {
	initSDL();
	renderer = SDLUtils::instance()->renderer();
	window = SDLUtils::instance()->window();

	gameStateMachine = new GameStateMachine();
	gameStateMachine->pushState(new PlayState());

	pause = false;
}

void Game::initSDL() {
	SDLUtils::instance(); // Crea la instancia de SDLUtils
}


Game::~Game(){ // destructora
	delete(gameStateMachine);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run(){ // bucle de juego
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {
		handlePause();
		if (!pause) 
		{
			frameTime = SDL_GetTicks() - startTime;
			if (frameTime >= FRAME_RATE) {
				update();
				gameStateMachine->clearStates(); // elimina estados
				startTime = SDL_GetTicks();
			}
			if (!exit) {
				SDL_RenderClear(renderer);
				render();
			}
		}
	}
}

void Game::update(){
	gameStateMachine->update();
}

void Game::render() { // Dibuja en pantalla el estado actual del juego
	SDL_RenderClear(renderer);
	gameStateMachine->render();
	SDL_RenderPresent(renderer); 
}

void Game::handlePause() {
	/*InputHandler::instance()->refresh();
	if (InputHandler::instance()->keyDownEvent()) {
		//Pausa SDL_SCANCODE_SPACE
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
			if (pause) pause = false;
			else pause = true;
		}
	}*/
}
