#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine(){// constructora
	clearStates();// borra los estados de la pila de borrado
	while (!st.empty()){// vacía la pila de estados
		delete(st.top());
		st.pop();
	}
}



GameState* GameStateMachine::currentState(){ // Devuelve estado actual
	return st.top();
}

void GameStateMachine::pushState(GameState* myState){ // Push del nuevo estado
	st.push(myState);
}

void GameStateMachine::changeState(GameState* myState) { // cambio de estado
	if (currentState()->getStateID() != myState->getStateID()) {
		popState();
		pushState(myState);
	}
}

void GameStateMachine::popState(){ // pop si la pila no está vacía y salida del estado
	if (!st.empty()){
		stToDelete.push(st.top());
		st.pop();
	}
}

void GameStateMachine::clearStates(){
	while (!stToDelete.empty()){
		delete(stToDelete.top());// elimina estado
		stToDelete.pop();// quita estado de la lista de eliminados
	}
}

void GameStateMachine::update() {
	currentState()->update();// update del estado actual
}

void GameStateMachine::render() {
	currentState()->render();// render del estado actual
}

