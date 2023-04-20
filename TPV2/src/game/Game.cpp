#include "Game.h"

Game::Game() {
	initSDL();// incio de SDL
	renderer = SDLUtils::instance()->renderer();// renderer
	window = SDLUtils::instance()->window();// ventana

	exit = false;// salida de juego a false
	manager = Manager::instance();
	manager->addSystem<FighterSystem>(_SYS_FIGHTER);
	manager->addSystem<GameCtrlSystem>(_SYS_GAMECTRL);
	manager->addSystem<AsteroidsSystem>(_SYS_ASTEROIDS);
	manager->addSystem<BulletSystem>(_SYS_BULLET);
	manager->addSystem<CollisionsSystem>(_SYS_COLLISIONS);
	manager->addSystem<RenderSystem>(_SYS_RENDER);
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
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit) {// bucle principal
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			SDL_RenderClear(renderer);
			InputHandler::instance()->refresh();// actualiza el input
			manager->updateSystems();
			SDL_RenderPresent(renderer);
			manager->refresh();
			startTime = SDL_GetTicks();
		}
	}
}


