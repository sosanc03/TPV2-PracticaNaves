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
	~GameStateMachine(); // destructora
	GameState* currentState(); // estado actual

	void pushState(GameState* myState); // push de un nuevo estado
	void popState();// quita un estado

	void changeState(GameState* myState);// cambia de estado
	void clearStates(); // borra los estados de la pila de borrado


	void update();// update
	void render();// render
};

