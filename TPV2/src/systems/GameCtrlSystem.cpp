#include "GameCtrlSystem.h"

void GameCtrlSystem::receive(const Message& m)
{
	switch (m.id) {

	case _MSG_COL_AST_PLAYER: // perder ronda
		onCollision_FighterAsteroid();
		break;
	case _MSG_NO_ASTEROIDS: // ganar 
		onAsteroidsExtinction();
		break;
	default:
		break;
	}
}

void GameCtrlSystem::initSystem() {
	winner_ = 0;
	fSys_ = mngr_->getSystem<FighterSystem>(_SYS_FIGHTER);
	Message m;
	state_ = 0; // pausa
	m.id = _MSG_START;
	mngr_->send(m);
}

void GameCtrlSystem::update() {
	if (InputHandler::instance()->keyDownEvent() && InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
		Message m;
		if (state_ == 1) {//running para pausar
			//Pausa
			state_ = 0;//pausa
			m.id = _MSG_PAUSE;
		}
		else {// reanudacion
			
			// victoria o perder todas las vidas
			if (winner_ == 2 || (fSys_ != nullptr && fSys_->fighter_->getComponent<Health>(HEALTH_H)->lifes == 0)) {
				m.id = _MSG_START;
				mngr_->send(m);
				m.id = _MSG_RESUME;
			}
				
			else {
				if (winner_ == 1) m.id = _MSG_GAMEOVER;//volver de perder una ronda
				else m.id = _MSG_RESUME; //volver de pausa
			}
			state_ = 1; // running
			winner_ = 0;
		}
		mngr_->send(m);
	}
}

void GameCtrlSystem::onCollision_FighterAsteroid() // derrota o perder vida
{
	state_ = 0;// pausa
	fSys_->fighter_->getComponent<Health>(HEALTH_H)->lifes--;// quita vida
	winner_ = 1;
}

void GameCtrlSystem::onAsteroidsExtinction() // victoria
{
	state_ = 0;// pausa
	winner_ = 2;
}
