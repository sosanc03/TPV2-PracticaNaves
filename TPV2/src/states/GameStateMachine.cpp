#include "GameStateMachine.h"
#include "../game/Game.h"

GameStateMachine::GameStateMachine(Game* Game) {
	game = Game;
}

GameStateMachine::~GameStateMachine(){
	clearStates();
	while (!states.empty()){
		delete(states.top());
		states.pop();
	}
}



GameState* GameStateMachine::currentState(){ // Devuelve estado actual
	return states.top();
}

void GameStateMachine::pushState(GameState* myState){ // Push del nuevo estado
	states.push(myState);
}

void GameStateMachine::changeState(GameState* myState) { // cambio de estado
	if (currentState()->getStateID() != myState->getStateID()) {
		popState();
		pushState(myState);
	}
}

void GameStateMachine::popState(){ // pop si la pila no está vacía y salida del estado
	if (!states.empty()){
		statesToDelete.push(states.top());
		states.pop();
	}
}

void GameStateMachine::clearStates(){
	while (!statesToDelete.empty()){
		delete(statesToDelete.top());// elimina estado
		statesToDelete.pop();// quita estado de la lista de eliminados
	}
}

void GameStateMachine::update() {
	currentState()->update();
}

void GameStateMachine::render() {
	currentState()->render();
}

