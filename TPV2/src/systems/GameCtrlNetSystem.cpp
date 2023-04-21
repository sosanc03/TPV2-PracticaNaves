#include "GameCtrlNetSystem.h"

GameCtrlNetSystem::GameCtrlNetSystem() :
	state_(_STOPPED) {
}

GameCtrlNetSystem::~GameCtrlNetSystem() {
}

void GameCtrlNetSystem::initSystem() {
}

void GameCtrlNetSystem::update() {
	auto& ihldr = ih();

	auto netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);

	if (!netSys->isReday())
		return;

	if (state_ != _RUNNING) {
		if (ihldr.isKeyDown(SDL_SCANCODE_SPACE)) {
			requestToStartGame();
		}
	}
}

void GameCtrlNetSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_COL_BULLET_PLAYER:
		handleBulletHitFighter(m);
		break;
	default:
		break;
	}
}

void GameCtrlNetSystem::requestToStartGame()
{
	if (mngr_->getSystem<NetworkSystem>(_SYS_NETWORK)->isHost()) {
		startGame();
	}
	else {
		mngr_->getSystem<NetworkSystem>(_SYS_NETWORK)->sendStarGameRequest();
	}
}

void GameCtrlNetSystem::startGame()
{
	if (state_ != _STOPPED)
		return;

	state_ = _RUNNING;
	Message m;
	m.id = _MSG_START;
	mngr_->send(m);
}



void GameCtrlNetSystem::gameOver()
{
	Message m;
	state_ = _STOPPED;

	m.id = _MSG_GAMEOVER;
	mngr_->send(m);
}


void GameCtrlNetSystem::handleBulletHitFighter(const Message& m) {
	state_ = _STOPPED;

	Message msg;
	msg.id = _MSG_GAMEOVER;
	msg.killed.playerId = m.bullet_fighter.fighter_->getComponent<FighterInfo>(FIGHTERINFO_H)->id_;
	msg.bullet_fighter.fighter_ = m.bullet_fighter.fighter_;
	mngr_->send(msg);
}
