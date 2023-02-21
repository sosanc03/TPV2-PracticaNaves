#include "GameStateMachine.h"
#include "GameState.h"

GameState::GameState() {
	gameStMachine = static_cast<GameStateMachine*>(GameStateMachine::instance());
}

void GameState::render() {

	Manager::instance()->render();
}

GameState::~GameState() // destructora
{
	Manager::instance()->~Manager();
}

void GameState::update() // ir a juego
{
	Manager::instance()->update();
}
