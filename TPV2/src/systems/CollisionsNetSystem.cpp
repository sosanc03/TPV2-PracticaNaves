#include "CollisionsNetSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "../ecs/Entity.h"

CollisionsNetSystem::CollisionsNetSystem() :
	running_(false) {
}

void CollisionsNetSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_START:
		handleGameStart(m);
		break;
	case _MSG_GAMEOVER:
		handleGameOver(m);
		break;
	default:
		break;
	}
}

CollisionsNetSystem::~CollisionsNetSystem() {
}

void CollisionsNetSystem::initSystem() {
}

void CollisionsNetSystem::update() {
	if (!running_)
		return;

	auto& fighters = mngr_->getEntitiesByGroup(_grp_FIGHTERS);
	auto& bullets = mngr_->getEntitiesByGroup(_grp_BULLETS);

	for (Entity* b : bullets) {
		if (!b->isAlive())
			continue;

		auto bTR = b->getComponent<Transform>(TRANSFORM_H);
		for (Entity* e : fighters) {
			auto eTR = e->getComponent<Transform>(TRANSFORM_H);


			if (Collisions::collidesWithRotation(bTR->pos_, bTR->w_,
				bTR->h_, bTR->rot_, //
				eTR->pos_, eTR->w_, eTR->h_, eTR->rot_)) {

				Message m;
				m.id = _MSG_COL_BULLET_PLAYER;
				m.bullet_fighter.bullet_ = b;
				m.bullet_fighter.fighter_ = e;
				mngr_->send(m);

				return;
			}
		}
	}
}

void CollisionsNetSystem::handleGameStart(const Message&) {
	running_ = true;
}

void CollisionsNetSystem::handleGameOver(const Message&) {
	running_ = false;
}
