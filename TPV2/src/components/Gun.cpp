//#include "Gun.h"
//
//Gun::Gun(float delayTime) : Component() {
//	delayTime_ = delayTime;// tiempo entre generaión de balas
//	lastTime_ = 0;// última generación
//	t_ = &(SDLUtils::instance()->images().at("bullet"));// textura
//	w_ = 10;// ancho
//	h_ = 25;// alto
//}
//
//void Gun::initComponent() {
//	tr_ = ent_->getComponent<Transform>(TRANSFORM_H);// transform
//}
//
//void Gun::update() {
//	if (ih().keyDownEvent()) {
//		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
//			if (sdlutils().currRealTime() >= lastTime_) {
//				createBullet();// genera bala
//				sdlutils().soundEffects().at("fire").play();// sonido de disparo
//				lastTime_ = sdlutils().currRealTime() + delayTime_;
//			}
//		}
//	}
//}
//
//void Gun::createBullet() {
//	Entity* bullet = mngr_->addEntity();// bala
//
//	int w = tr_->getW(); int h = tr_->getH(); float r = tr_->getR();// ancho, alto y rotación
//	
//	Vector2D bPos = tr_->getPos()
//		+ Vector2D(w / 2.0f, h / 2.0f)
//		- Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r)
//		- Vector2D(2.0f, 10.0f);// posición
//	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(r) * (tr_->getVel().magnitude() + 5.0f);// velocidad
//
//	bullet->addComponent<Transform>(TRANSFORM_H, bPos, bVel, w_, h_, r);// transform
//	bullet->addComponent<Image>(IMAGE_H, t_);// componente image
//	bullet->addComponent<DisableOnExit>(DISABLEONEXIT_H);// conmponente de desactivar al desaparecer
//
//	bullet->addToGroup(_grp_BULLETS);// añade al grupo de balas
//}