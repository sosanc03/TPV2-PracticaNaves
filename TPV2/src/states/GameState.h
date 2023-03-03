#pragma once
#include <string>
#include <list>
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"


using namespace std;

class GameState{
public:
	GameState();// constructora
	virtual ~GameState(); // destructora
	virtual void update();// update
	virtual void render();// render
	virtual string getStateID() = 0;// id
};

