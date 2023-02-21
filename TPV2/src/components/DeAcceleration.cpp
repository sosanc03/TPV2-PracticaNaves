#include "DeAcceleration.h"

DeAcceleration::DeAcceleration(float DeaccelerationFactor, float Limit) {
	deaccelerationFactor = DeaccelerationFactor;
	limit = Limit;
}

DeAcceleration::~DeAcceleration() {
}

void DeAcceleration::initComponent() {
	tr = ent_->getComponent<Transform>(_TRANSFORM);
}

void DeAcceleration::update() {
	if (tr->getVel().magnitude() <= limit) { tr->setVel(Vector2D(0, 0)); }
	else { tr->setVel(tr->getVel() * deaccelerationFactor); }
}