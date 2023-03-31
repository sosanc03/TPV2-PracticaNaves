#include "GameCtrlSystem.h"

void GameCtrlSystem::receive(const Message& m)
{
	switch (m.id) {

	case _MSG_COL_AST_PLAYER:
		onCollision_FighterAsteroid();
		break;
	case _MSG_NO_ASTEROIDS:
		onAsteroidsExtinction();
		break;
	default:
		break;
	}
}

void GameCtrlSystem::initSystem() {
	Message m;
	state_ = 1; // running
	m.id = _MSG_START;
	mngr_->send(m);
}

void GameCtrlSystem::update() {
	if (state_ == 1) {//runing
		InputHandler::instance()->refresh();
		if (InputHandler::instance()->keyDownEvent()) {
			//Pausa SDL_SCANCODE_SPACE
			if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
				state_ = 0;//pausa
			}
		}
	}
	else {// pausa
		if (mngr_->getComponent<Health>(mngr_->getHandler(ecs::_HDLR_PLAYER))->lifes == 0) initSystem();
		else {
			Message m;
			state_ = 1; // running
			m.id = _MSG_RESUME;
			mngr_->send(m);
		}
	}
}


void GameCtrlSystem::onCollision_FighterAsteroid() // derrota o perder vida
{
	state_ = 0;// pausa
	mngr_->getComponent<Health>(mngr_->getHandler(ecs::_HDLR_PLAYER))->lifes--;// quita vida
}

void GameCtrlSystem::onAsteroidsExtinction() // victoria
{
	state_ = 0;// pausa
}
