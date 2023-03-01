#include "FighterCtrl.h"

FighterCtrl::FighterCtrl(float maxVel, float rot, float thrust) :Component() {
	maxVel_ = maxVel;
	rot_ = rot;
	thrust_ = thrust;
}

void FighterCtrl::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
	tr_->setDir();
}

void FighterCtrl::update() {
	if (InputHandler::instance()->keyDownEvent()) {
		//Rotación
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
			tr_->setR(-rot_);
		}
		else if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
			tr_->setR(rot_);
		}
		//Movimiento
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_UP)) {
			tr_->setVel(tr_->getVel() + (tr_->getDir() * thrust_));
			sdlutils().soundEffects().at("thrust").play();
		}
	}
}