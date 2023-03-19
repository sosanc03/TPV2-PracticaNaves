#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"

using namespace ecs;

struct Follow : public Component
{
public:
	Follow() {};



//private:
//#pragma region references
//	Entity* figther_;// nave
//	Transform* tr_;// transform
//	Transform* playerTr_;// transform de la nave
//#pragma endregion
//
//#pragma region propierties
//	Vector2D dir_;// dirección
//#pragma endregion
//
//
//public:
//	Follow(Entity* player) {// constructora
//		figther_ = player;
//	}
//
//	void initComponent() {// init
//		tr_ = ent_->getComponent<Transform>(TRANSFORM_H);// transform de la entidad
//		playerTr_ = figther_->getComponent<Transform>(TRANSFORM_H);// transdorm de la nave
//	}
//
//	void update() {
//		dir_ = Vector2D(playerTr_->getPos().getX() - tr_->getPos().getX(),
//			playerTr_->getPos().getY() - tr_->getPos().getY());// setea la dirección
//		dir_ = dir_.normalize();// normaliza la dirección
//		tr_->setVel(dir_);// setea la dirección 
//	}
};

