#include "GameCtrlNetSystem.h"
#include "../ecs/Entity.h"

GameCtrlNetSystem::GameCtrlNetSystem() :
	state_(PAUSED) {
}

GameCtrlNetSystem::~GameCtrlNetSystem() {
}

void GameCtrlNetSystem::update() {

	NetworkSystem* netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);

	if (!netSys->isReady()) return;// comprueba que los dos jugadores están conectados
	if (state_ != RUNNING && InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) requestToStartGame();// inicio de juego
}

void GameCtrlNetSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_COL_BULLET_PLAYER:// colision entre bala y jugador
		GameOver(m);
		break;
	default:
		break;
	}
}

// se llama al pulsar espacio
void GameCtrlNetSystem::requestToStartGame() {
	if (mngr_->getSystem<NetworkSystem>(_SYS_NETWORK)->isHost()) GameStart();// se inicia el juego si host es true
	else mngr_->getSystem<NetworkSystem>(_SYS_NETWORK)->sendStarGameRequest();// se solicita inicio de juego
}

void GameCtrlNetSystem::GameStart()
{
	if (state_ != PAUSED) return;

	// inicio de juego
	state_ = RUNNING;
	Message m;
	m.id = _MSG_START;
	mngr_->send(m);
}

void GameCtrlNetSystem::GameOver(const Message& m)
{
	// fin de juego
	state_ = PAUSED;

	Message msg;
	msg.id = _MSG_GAMEOVER;

	msg.killed.playerId = m.bullet_fighter.fighter_->getComponent<FighterInfo>(FIGHTERINFO_H)->id_;// guarda el id del player golpeado por la bala
	msg.bullet_fighter.fighter_ = m.bullet_fighter.fighter_;
	mngr_->send(msg);

}
