#pragma once
#include <string>
#include <list>
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"


using namespace std;

class GameState{
public:
	GameState();
	virtual ~GameState(); 
	virtual void update();
	virtual void render();
	virtual string getStateID() = 0;
};

