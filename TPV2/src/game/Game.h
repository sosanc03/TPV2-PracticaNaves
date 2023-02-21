#pragma once

#include <iostream>
#include "SDL.h" 
#include "../sdlutils/SDLUtils.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"

using namespace std;

using uint = unsigned int;

//CONSTANTES
const uint FRAME_RATE = 3;
const uint FIGHTER_SIZE = 75;


class Game :public Singleton <Game>{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStateMachine;
	bool exit;

public:
	Game();
	void initSDL();
	virtual ~Game();
	void update();
	void render();
	void run();
};
