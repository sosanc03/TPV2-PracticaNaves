// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/messages.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "GameCtrlSystem.h"

CollisionsSystem::CollisionsSystem() :
	active_(false) {
}

CollisionsSystem::~CollisionsSystem() {
}

void CollisionsSystem::initSystem() {

}

void CollisionsSystem::update() {

	if (active_) {
		//Pointer to the player
		auto playerTr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_PLAYER));

		//main asterid loop
		for (auto e : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {

			//Transform of the asteroid
			auto metheorTr_ = mngr_->getComponent<Transform>(e);
			
			//Collision between asteroid and player
			if (Collisions::collides(metheorTr_->pos_, metheorTr_->width_,
				metheorTr_->height_, playerTr_->pos_, playerTr_->width_,
				playerTr_->height_)) {
				Message m;
				m.id = _m_COL_AST_PLAYER;
				mngr_->send(m);
				break;
			}

			//For each asteroid, we check collisions with all the bullets 
			for (auto bullet : mngr_->getEntities(ecs::_grp_BULLETS)) {
				//Transform for the bullet
				auto bulletTr_ = mngr_->getComponent<Transform>(bullet);

				//Collision
				if (Collisions::collides(metheorTr_->pos_, metheorTr_->width_,
					metheorTr_->height_, bulletTr_->pos_, bulletTr_->width_,
					bulletTr_->height_)) {
					Message m;
					m.id = _m_COL_BULLET_AST;
					m.bullet_hit_asteroid.ast = e;
					m.bullet_hit_asteroid.bull = bullet;
					mngr_->send(m);
				}
			}
		}
	}

}

void CollisionsSystem::recieve(const Message& m) {
	switch (m.id) {
	case _m_COL_AST_PLAYER:
		active_ = false;
		break;
	case _m_GAME_START:
		active_ = true;
		break;
	case _m_GAME_RESUME:
		active_ = true;
	default:
		break;
	}
}
