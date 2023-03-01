#include "DeAcceleration.h"

DeAcceleration::DeAcceleration() {
	deaF_ = 0.995f;
	limit_ = 0.005;
}

DeAcceleration::~DeAcceleration() {
}

void DeAcceleration::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
}

void DeAcceleration::update() {
	if (tr_->getVel().magnitude() <= limit_) tr_->setVel(Vector2D(0, 0));
	else tr_->setVel(tr_->getVel() * deaF_); 
}