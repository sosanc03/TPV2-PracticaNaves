#include "CollisionsSystem.h"

void CollisionsSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_COL_AST_PLAYER:
		onRoundOver();
		break;
	case _MSG_START:
		initSystem();
		break;
	case _MSG_RESUME:
		onRoundStart();
	default:
		break;
	}
}

void CollisionsSystem::initSystem() {
	active_ = true;
}

void CollisionsSystem::update() {
	checkCollision();
}

void CollisionsSystem::checkCollision()
{
	Transform* plTr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_HDLR_PLAYER));
	for (auto as : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {// recorre las entidades y comprueba que sea un asteroide
		Transform* asTr_ = mngr_->getComponent<Transform>(as);
		if (collides(plTr_, asTr_)) // colision entre asteroide y player
		{
			Message m;
			m.id = _MSG_COL_AST_PLAYER;
			mngr_->send(m);
		}
		else {
			for (auto b : mngr_->getEntities(ecs::_grp_BULLETS)) {// recorre las entidades y comprueba que sea una bala
					Transform* bTr_ = mngr_->getComponent<Transform>(b);
					if (collides(bTr_, asTr_)) // colisión entre bala y asteroide
					{
						Message m;
						m.id = _MSG_COL_AST_BULLET;
						m.hitBulAst.asteroid_ = as;
						m.hitBulAst.bullet_ = b;
						mngr_->send(m);

						/*astM_->onCollision(as);
						b->removeFromGroup(_grp_BULLETS);
						b->setAlive(false);*/
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