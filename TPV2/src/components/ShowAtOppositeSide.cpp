//#include "ShowAtOpposideSide.h"
//
//void ShowAtOppositeSide::initComponent() {
//	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);// transform
//	margin_ = 20;// margen
//	wWidth_ = sdlutils().width();// ancho de ventana
//	wHeight_ = sdlutils().height();// alto de ventana
//	w_ = tr_->getW();// ancho
//	h_ = tr_->getH();// altura
//
//}
//
//void ShowAtOppositeSide::update() {
//	Vector2D pos_ = tr_->getPos();// posición
//
//	// X
//	if (pos_.getX() > wWidth_ + margin_) { tr_->setPosX(0 - margin_); }
//	else if (pos_.getX() < 0 - margin_) { tr_->setPosX(wWidth_ + margin_); }
//
//	// Y
//	if (pos_.getY() > wHeight_ + margin_) { tr_->setPosY(0 - margin_); }
//	else if (pos_.getY() < 0 - margin_) { tr_->setPosY(wHeight_ + margin_); }
//}