#pragma once

#include <iostream>
#include "SDL.h" 
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"
#include "../systems/FighterSystem.h"
#include "../systems/AsteroidsSystem.h"
#include "../systems/BulletSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
//#include "../systems/NetworkSystem.h"
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
	Manager* manager = nullptr;
	bool exit, started, pressed, multi;// booleano de salida
	string nombre;
	//NetworkSystem* netSys_;
public:
	Game();// contructora
	void initSDL();// inicio de SDL
	virtual ~Game();// destructora
	void run(); // ejecución

};
