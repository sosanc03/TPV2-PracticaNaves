#include "CollisionsNetSystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../utils/Collisions.h"
#include "../ecs/Entity.h"

CollisionsNetSystem::CollisionsNetSystem() {
	active_ = false;
}

void CollisionsNetSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_START:
		GameStart(m);
		break;
	case _MSG_GAMEOVER:
		GameOver(m);
		break;
	default:
		break;
	}
}

CollisionsNetSystem::~CollisionsNetSystem() {
}

void CollisionsNetSystem::update() {
	if (!active_)
		return;
	checkCollision();
}

void CollisionsNetSystem::checkCollision() {
	auto& fighters = mngr_->getEntitiesByGroup(_grp_FIGHTERS);
	auto& bullets = mngr_->getEntitiesByGroup(_grp_BULLETS);

	for (Entity* b : bullets) {
		if (!b->isAlive())
			continue;

		Transform* btr_ = b->getComponent<Transform>(TRANSFORM_H);
		for (Entity* e : fighters) {
			FighterInfo* fi_ = e->getComponent<FighterInfo>(FIGHTERINFO_H);
			BulletInfo* bu_ = b->getComponent<BulletInfo>(BULLETINFO_H);

			Transform* etr_ = e->getComponent<Transform>(TRANSFORM_H);

			if (fi_->id_ != bu_->id_ && collides(etr_, btr_)) {

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

bool CollisionsNetSystem::collides(Transform* obj1_, Transform* obj2_) {
	return (Collisions::collidesWithRotation(obj1_->pos_, obj1_->w_,
		obj1_->h_, obj1_->rot_, obj2_->pos_, obj2_->w_,
		obj2_->h_, obj2_->rot_));
}

void CollisionsNetSystem::GameStart(const Message&) {
	active_ = true;
}

void CollisionsNetSystem::GameOver(const Message&) {
	active_ = false;
}
