// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../components/FighterInfo.h"
#include "../ecs/Manager.h"
#include "../game/messages_defs.h"
#include "../sdlutils/InputHandler.h"
#include "../systems/NetworkSystem.h"

GameCtrlSystem::GameCtrlSystem() :
	state_(_STOPPED) {
}

GameCtrlSystem::~GameCtrlSystem() {
}

void GameCtrlSystem::initSystem() {
}

void GameCtrlSystem::update() {
	auto& ihldr = ih();

	auto netSys = mngr_->getSystem<NetworkSystem>();

	if (!netSys->isReday())
		return;

	if (state_ != _RUNNING) {
		if (ihldr.isKeyDown(SDL_SCANCODE_SPACE)) {
			requestToStartGame();
		}
	}
}

void GameCtrlSystem::recieve(const Message& m) {
	switch (m.id) {
	case _m_BULLET_HIT_FIGHTER:
		handleBulletHitFighter(m);
		break;
	default:
		break;
	}
}

void GameCtrlSystem::requestToStartGame()
{
	if (mngr_->getSystem<NetworkSystem>()->isHost()) {
		startGame();
	}
	else {
		mngr_->getSystem<NetworkSystem>()->sendStarGameRequest();
	}
}

void GameCtrlSystem::startGame()
{
	if (state_ != _STOPPED)
		return;

	state_ = _RUNNING;
	Message m;
	m.id = _m_GAME_START;
	mngr_->send(m);
}



void GameCtrlSystem::gameOver()
{
	Message m;
	state_ = _STOPPED;

	m.id = _m_GAME_OVER;
	mngr_->send(m);
}

void GameCtrlSystem::stopTheGame()
{
	Message m;
	state_ = _STOPPED;
	m.id = _m_NEW_GAME;
	mngr_->send(m);
}

void GameCtrlSystem::handleBulletHitFighter(const Message& m) {
	state_ = _STOPPED;

	Message msg;
	msg.id = _m_GAME_OVER;
	msg.killed.playerId = mngr_->getComponent<FighterInfo>
		(m.bullet_hit.fighter_)->id_;

	msg.bullet_hit.fighter_ = m.bullet_hit.fighter_;
	mngr_->send(msg);
}
