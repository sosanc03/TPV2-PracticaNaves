#include "Game.h"

Game::Game() {
	initSDL();// incio de SDL
	renderer = SDLUtils::instance()->renderer();// renderer
	window = SDLUtils::instance()->window();// ventana

	pressed = started = exit = false;// salida de juego a false
	manager = Manager::instance();
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
	while (!exit) {
		if (started) {
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
		else {
			if (!pressed) {
				auto& t = sdlutils().msgs().at("mainMenu1"); // espacio para continuar
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 + t.height() * 2);
				auto& t2 = sdlutils().msgs().at("mainMenu2");
				t2.render((sdlutils().width() - t2.width()) / 2,
					sdlutils().height() / 4 + t2.height() * 2);
				SDL_RenderPresent(renderer);
			}
			while (!pressed) {
				InputHandler::instance()->refresh();// actualiza el input
				if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_1)) {
					pressed = true;
					multi = false; // solitario
					started = true;
				}
				else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_2)) {
					pressed = true;
					multi = true; // multijugador
				}
			}
			if (pressed) {
				// inicio modo solitario
				if (!multi) {
					manager->addSystem<FighterSystem>(_SYS_FIGHTER);
					manager->addSystem<GameCtrlSystem>(_SYS_GAMECTRL);
					manager->addSystem<AsteroidsSystem>(_SYS_ASTEROIDS);
					manager->addSystem<BulletSystem>(_SYS_BULLET);
					manager->addSystem<CollisionsSystem>(_SYS_COLLISIONS);
					manager->addSystem<RenderSystem>(_SYS_RENDER);
				}
				// preguntar nombre en multijugador
				else {
					SDL_RenderClear(renderer);
					auto& t = sdlutils().msgs().at("nombre"); // espacio para continuar
					t.render((sdlutils().width() - t.width()) / 2,
						sdlutils().height() / 2 - t.height());
					SDL_RenderPresent(renderer);
					/*netSys_ = manager->addSystem<NetworkSystem>(_SYS_NETWORK);
					netSys_->putName();
					if (!netSys_->connect()) cout << "No hay Network >:(";*/

					// add the systems
					/*manager->addSystem<GameCtrlNetSystem>(_SYS_GAMECTRLNET);
					manager->addSystem<FighterCtrlNetSystem>(_SYS_FIGHTERNET);
					manager->addSystem<BulletNetSystem>(_SYS_BULLETNET);*/
					/*manager->addSystem<RenderNetSystem>(_SYS_RENDERNET);
					manager->addSystem<CollisionNetSystem>(_SYS_COLLISIONSNET);*/
					started = true;
				}
			}
		}
	}
	
	
}


