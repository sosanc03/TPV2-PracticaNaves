#pragma once

#include <iostream>
#include "SDL.h" 
#include "../sdlutils/SDLUtils.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"
#include "../states/PauseState.h"

using namespace std;

using uint = unsigned int;

//CONSTANTES
const uint FRAME_RATE = 15;
const uint FIGHTER_SIZE = 60;
const uint ANIMATION_SPEED = 10;

class Game :public Singleton <Game>{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine* gameStateMachine;

	bool exit, pause;

public:
	Game();
	void initSDL();
	virtual ~Game();
	void update();
	void render();
	void run();
	SDL_Renderer* getRenderer() { return renderer; }
};
