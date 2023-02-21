#include "Game.h"

Game::Game() {
	initSDL();
	renderer = SDLUtils::instance()->renderer();
	window = SDLUtils::instance()->window();

	gameStateMachine = new GameStateMachine();
	gameStateMachine->pushState(new PlayState());
}

void Game::initSDL() {
	/*
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { cout << "SDL init success\n"; } // Initialize SDL
	window = SDL_CreateWindow("Asteroids", 0, 25, WIN_W, WIN_H, 0); // Init the window
	if (window != nullptr) { cout << "window creation success\n"; }
	renderer = SDL_CreateRenderer(window, -1, 0); // Init the renderer
	if (renderer != nullptr) { cout << "renderer creation success\n"; }
	*/

	SDLUtils::instance(); // Crea la instancia de SDLUtils
}

/*while (!exit_) {
	…
		manager_->update();
	…
		sdlutils().clearRenderer();
	manager_->render();
	sdlutils().presentRenderer();
	…
		manager_->refresh();
	…
}*/


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

		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE){
			update();
			gameStateMachine->clearStates(); // elimina estados
			startTime = SDL_GetTicks();
		}
		if (!exit){
			SDL_RenderClear(renderer);
			render();
			SDL_Delay(10);
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