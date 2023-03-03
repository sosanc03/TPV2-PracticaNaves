#include "FighterCtrl.h"

FighterCtrl::FighterCtrl(float maxVel, float rot, float thrust) :Component() {
	maxVel_ = maxVel;// m�xima velocidad
	rot_ = rot;// rotaci�n
	thrust_ = thrust;// empuje
}

void FighterCtrl::initComponent() {// init
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);// transform
	tr_->setDir();// setea la direcci�n
}

void FighterCtrl::update() {
	if (InputHandler::instance()->keyDownEvent()) {
		//Rotaci�n
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
			tr_->setR(-rot_);
		}
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
			tr_->setR(rot_);
		}
		//Movimiento
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_UP)) {
			tr_->setVel(tr_->getVel() + (tr_->getDir() * thrust_));
			sdlutils().soundEffects().at("thrust").play();
		}
	}
}