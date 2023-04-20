#include "CollisionsSystem.h"

void CollisionsSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_COL_AST_PLAYER: // perder ronda
		onRoundOver();
		break;
	case _MSG_START: // iniciar partida
		initSystem();
		break;
	case _MSG_RESUME: // resume
		onRoundStart();
	case _MSG_GAMEOVER: // volver de perder ronda
		active_ = true;
		break;
	default:
		break;
	}
}

void CollisionsSystem::initSystem() {
	active_ = true;
	fSys_ = mngr_->getSystem<FighterSystem>(_SYS_FIGHTER);
}

void CollisionsSystem::update() {
	if(active_)checkCollision();
}

void CollisionsSystem::checkCollision()
{
	Transform* plTr_ = fSys_->fighter_->getComponent<Transform>(TRANSFORM_H);
	for (auto as : mngr_->getEntitiesByGroup(_grp_ASTEROIDS)) {// recorre las entidades y comprueba que sea un asteroide
		Transform* asTr_ = as->getComponent<Transform>(TRANSFORM_H);
		if (collides(plTr_, asTr_)) // colision entre asteroide y player
		{
			Message m;
			m.id = _MSG_COL_AST_PLAYER;
			mngr_->send(m);
		}
		else {
			for (auto b : mngr_->getEntitiesByGroup(_grp_BULLETS)) {// recorre las entidades y comprueba que sea una bala
					Transform* bTr_ = b->getComponent<Transform>(TRANSFORM_H);
					if (collides(bTr_, asTr_)) // colisión entre bala y asteroide
					{
						Message m;
						m.id = _MSG_COL_AST_BULLET;
						m.hitBulAst.asteroid_ = as;
						m.hitBulAst.bullet_ = b;
						mngr_->send(m);
					}
			}
		}
	}
}

bool CollisionsSystem::collides(Transform* obj1_, Transform* obj2_) {
	return (Collisions::collidesWithRotation(obj1_->pos_, obj1_->w_,
		obj1_->h_, obj1_->rot_, obj2_->pos_, obj2_->w_,
		obj2_->h_, obj2_->rot_));
}


void CollisionsSystem::onRoundOver() {
	active_ = false;
}

void CollisionsSystem::onRoundStart() {
	active_ = true;
}