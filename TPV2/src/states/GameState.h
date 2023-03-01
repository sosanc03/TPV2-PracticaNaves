#pragma once
#include <string>
#include <list>
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"

class GameStateMachine;

using namespace std;

class GameState{
protected:
	GameStateMachine* gameStMachine; 
public:
	GameState();
	virtual ~GameState(); 
	virtual void update();
	virtual void render();
	virtual string getStateID() = 0;
};

