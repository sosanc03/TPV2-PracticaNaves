#pragma once

#include <iostream>
#include "SDL.h" 
#include "../sdlutils/SDLUtils.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"

using namespace std;

using uint = unsigned int;

//CONSTANTES
const uint FRAME_RATE = 15;
const uint FIGHTER_SIZE = 60;
const uint ANIMATION_SPEED = 10;

class Game :public Singleton <Game>{
private:
	SDL_Window* window = nullptr;// ventana
	SDL_Renderer* renderer = nullptr;// renderer

	bool exit;// booleano de salida

public:
	Game();// contructora
	void initSDL();// inicio de SDL
	virtual ~Game();// destructora
	void update();// udate
	void render();// render
	void run(); // ejecución

};
