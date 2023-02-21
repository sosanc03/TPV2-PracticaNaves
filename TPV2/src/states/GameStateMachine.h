#pragma once
#include "../utils/Singleton.h"
#include <stack>
#include "../ecs/Manager.h"
#include "GameState.h"

class GameStateMachine: public Singleton <GameStateMachine> {
private:
	stack<GameState*> st; // pila de escenas
	stack<GameState*> stToDelete; // pila de escenas a borrar
public:
	~GameStateMachine(); 
	GameState* currentState(); 

	void pushState(GameState* myState); 
	void popState();

	void changeState(GameState* myState);
	void clearStates(); 


	void update();
	void render();
};

