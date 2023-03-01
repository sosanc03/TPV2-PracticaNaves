#include "Gun.h"

Gun::Gun(float delayTime) : Component() {
	delayTime_ = delayTime;
	lastTime_ = 0;
	t_ = &(SDLUtils::instance()->images().at("bullet"));
	w_ = 10;
	h_ = 25;
}

void Gun::initComponent() {
	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);
}

void Gun::update() {
	if (ih().keyDownEvent()) {
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
			if (sdlutils().currRealTime() >= lastTime_) {
				createBullet();
				sdlutils().soundEffects().at("fire").play();
				lastTime_ = sdlutils().currRealTime() + delayTime_;
			}
		}
	}
}

void Gun::createBullet() {
	Entity* bullet = mngr_->addEntity();

	int w = tr_->getW(); int h = tr_->getH(); float r = tr_->getR();
	
	Vector2D bPos = tr_->getPos()
		+ Vector2D(w / 2.0f, h / 2.0f)
		- Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r)
		- Vector2D(2.0f, 10.0f);
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(r) * (tr_->getVel().magnitude() + 5.0f);

	bullet->addComponent<Transform>(TRANSFORM_H, bPos, bVel, w_, h_, r);
	bullet->addComponent<Image>(IMAGE_H, t_);
	bullet->addComponent<DisableOnExit>(DISABLEONEXIT_H);

	bullet->addToGroup(_grp_BULLETS);
}