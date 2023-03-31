#pragma once

#include <iostream>
#include "SDL.h" 
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/AsteroidsSystem.h"
#include "../systems/BulletSystem.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"

using namespace std;

using uint = unsigned int;

//CONSTANTES
const uint FRAME_RATE = 15;
const uint FIGHTER_SIZE = 60;
const uint ANIMATION_SPEED = 10;

class FighterSystem;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	ecs::Manager* mngr_;


	GameCtrlSystem* gameCtrlSys_;
	CollisionsSystem* collisionsSys_;
	RenderSystem* renderSys_;
	FighterSystem* fightSys_;
	AsteroidsSystem* AstSys_;
	BulletSystem* BullSys_;
};