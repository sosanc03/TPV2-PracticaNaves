#include "ShowAtOpposideSide.h"

void ShowAtOppositeSide::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	margin_ = 20;
	wWidth_ = sdlutils().width();
	wHeight_ = sdlutils().height();
	w_ = tr_->getW();
	h_ = tr_->getH();

}

void ShowAtOppositeSide::update() {
	Vector2D pos_ = tr_->getPos();

	// X
	if (pos_.getX() > wWidth_ + margin_) { tr_->setPosX(0 - margin_); }
	else if (pos_.getX() < 0 - margin_) { tr_->setPosX(wWidth_ + margin_); }

	// Y
	if (pos_.getY() > wHeight_ + margin_) { tr_->setPosY(0 - margin_); }
	else if (pos_.getY() < 0 - margin_) { tr_->setPosY(wHeight_ + margin_); }
}