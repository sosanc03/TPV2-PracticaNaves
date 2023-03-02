#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"

using namespace ecs;

class Follow : public Component
{
private:
#pragma region references
	Entity* figther_;
	Transform* tr_;
	Transform* playerTr_;
#pragma endregion

#pragma region propierties
	Vector2D dir_;
#pragma endregion


public:
	Follow(Entity* player) {
		figther_ = player;
	}

	void initComponent() {
		tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
		playerTr_ = figther_->getComponent<Transform>(TRANSFORM_H);
	}

	void update() {
		dir_ = Vector2D(playerTr_->getPos().getX() - tr_->getPos().getX(),
			playerTr_->getPos().getY() - tr_->getPos().getY());
		dir_ = dir_.normalize();
		tr_->setVel(dir_);
	}
};

