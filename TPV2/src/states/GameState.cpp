#include "GameState.h"

GameState::GameState() {
	
}

void GameState::render() {
	Manager::instance()->render();
}

GameState::~GameState() // destructora
{
	
}

void GameState::update() // ir a juego
{
	Manager::instance()->update();
	Manager::instance()->refresh();
}
