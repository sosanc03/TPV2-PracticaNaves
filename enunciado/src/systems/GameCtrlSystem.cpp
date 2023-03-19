// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrlSystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Health.h"

GameCtrlSystem::GameCtrlSystem() :
	state_(NEWGAME) {
}

GameCtrlSystem::~GameCtrlSystem() {
}


void GameCtrlSystem::update() {
	if (state_ != RUNNING) {

		auto& inhdlr = ih();

		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case NEWGAME: //If in menu to Start
				newGame();
				break;
			case PAUSED: //If hit once or twice, start a new round, else start a new game
				if (mngr_->getComponent<Health>(mngr_->getHandler(ecs::_hdlr_PLAYER))->h_ == 0 || win) {
					win = false; state_ = NEWGAME;
				}
				else startRound();
				break;
			default:
				break;
			}
			//getsystem y dependiendo del estado renderiza una cosa o otra
		}
	}
	

}

void GameCtrlSystem::recieve(const Message& m) {
	switch (m.id) {

	case _m_COL_AST_PLAYER:
		state_ = PAUSED;
		break;
	case _m_NO_ASTEROIDS:
		state_ = PAUSED;
		win = true;
		break;
	default:
		break;
	}
}

bool GameCtrlSystem::hasWin()
{
	return win;
}

void GameCtrlSystem::startRound() {
	Message m;
	state_ = RUNNING;
	m.id = _m_GAME_RESUME;
	mngr_->send(m);
}


void GameCtrlSystem::roundOver() {
	Message m;
	state_ = PAUSED;
	m.id = _m_GAME_PAUSED;
	mngr_->send(m);
}

//void GameCtrlSystem::gameOver() {
//	Message m;
//	state_ = GAMEOVER;
//	m.id = _m_GAME_OVER;
//	mngr_->send(m);
//}

void GameCtrlSystem::newGame()
{
	Message m;
	state_ = RUNNING;
	m.id = _m_GAME_START;
	mngr_->send(m);
}
