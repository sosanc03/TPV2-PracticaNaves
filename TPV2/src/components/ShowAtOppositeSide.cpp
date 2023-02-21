#include "ShowAtOpposideSide.h"

void ShowAtOppositeSide::initComponent() {
	tr = ent_->getComponent<Transform>(_TRANSFORM);
}

void ShowAtOppositeSide::update() {
	Vector2D pos = tr->getPos();
	float w = tr->getW();
	float h = tr->getH();
	
	// Comprueba eje X
	if (pos.getX() > WIDTH) { tr->setPosX(0 - w); }
	else if (pos.getX() < 0 - w) { tr->setPosX(WIDTH); }

	// Comprueba eje Y
	if (pos.getY() > HEIGHT) { tr->setPosY(0 - h); }
	else if(pos.getY() < 0 - h){ tr->setPosY(HEIGHT); }
}