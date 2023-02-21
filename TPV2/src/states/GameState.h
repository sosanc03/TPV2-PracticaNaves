#pragma once
#include <string>
#include <list>
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"

class GameStateMachine;

using namespace std;

class GameState{
protected:
	GameStateMachine* gameStateMachine; 
public:
	GameState();
	virtual ~GameState(); 
	virtual void update();
	virtual void render();
	virtual string getStateID() = 0;
};
