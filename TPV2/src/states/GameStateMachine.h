#pragma once
#include "../utils/Singleton.h"
#include <stack>
#include "../ecs/Manager.h"
#include "GameState.h"

class Game;

class GameStateMachine: public Singleton <GameStateMachine> {
private:
	stack<GameState*> states; // pila de escenas
	stack<GameState*> statesToDelete; // pila de escenas a borrar
	Game* game;
public:
	GameStateMachine() {}
	GameStateMachine(Game* Game);
	~GameStateMachine(); 
	GameState* currentState(); 

	void pushState(GameState* myState); 
	void popState();

	void changeState(GameState* myState);
	void clearStates(); 


	void update();
	void render();
};

