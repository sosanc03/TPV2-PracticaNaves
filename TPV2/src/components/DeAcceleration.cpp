#include "DeAcceleration.h"

DeAcceleration::DeAcceleration() {
	deaFactor = 0.995f;
	limit = 0.005;
}

DeAcceleration::~DeAcceleration() {
}

void DeAcceleration::initComponent() {
	tr = ent_->getComponent<Transform>(_TRANSFORM);
}

void DeAcceleration::update() {
	if (tr->getVel().magnitude() <= limit) tr->setVel(Vector2D(0, 0));
	else tr->setVel(tr->getVel() * deaFactor); 
}