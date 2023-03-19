/*#include "DeAcceleration.h"

DeAcceleration::DeAcceleration() {
	deaF_ = 0.995f;// factor de deceleración
	limit_ = 0.005;// mínimo de velocidad antes de que la nave se pare
}


void DeAcceleration::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);// transform
}

void DeAcceleration::update() {
	if (tr_->getVel().magnitude() <= limit_) tr_->setVel(Vector2D(0, 0));// nave parada
	else tr_->setVel(tr_->getVel() * deaF_); // velocidad 
}*/