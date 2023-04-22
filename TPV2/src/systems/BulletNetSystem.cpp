#include "BulletNetSystem.h"

BulletNetSystem::BulletNetSystem() :
	running_(false) {
}

BulletNetSystem::~BulletNetSystem() {
}

void BulletNetSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_SHOT:
		shoot(m);
		break;
	case _MSG_GAMEOVER:
		GameOver(m);
		break;
	case _MSG_START:
		GameStart(m);
		break;
	default:
		break;
	}
}

void BulletNetSystem::initSystem() {
}

void BulletNetSystem::update() {
	if (!running_)
		return;
	auto netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);

	for (Entity* b : mngr_->getEntitiesByGroup(_grp_BULLETS)) {
		Transform* bTR = b->getComponent<Transform>(TRANSFORM_H);

		// disable if exit from window
		DisableOnExitUpdate(b, bTR);

		// move the bullet
		bTR->move();

		netSys->sendBulletPosition(bTR);
	}
}

void BulletNetSystem::createBullet(float posX, float posY, float velX, float velY, int id)
{
	if (sdlutils().currRealTime() >= cont_) {
		cont_ = sdlutils().currRealTime() + 250; // 250ms

		sdlutils().soundEffects().at("fire").play(); // sonido disparo

		Entity* bullet = mngr_->addEntity(_grp_BULLETS);// bala

		int w_ = 10;// ancho
		int h_ = 25;// alto
		auto t = &sdlutils().images().at("bullet");
		Vector2D pos = Vector2D(posX, posY);
		Vector2D vel = Vector2D(velX, velY);
		float r = Vector2D(0.0f, -1.0f).angle(vel);
		bullet->addComponent<Transform>(TRANSFORM_H, pos, vel, w_, h_, r);// transform
		bullet->addComponent<Image>(IMAGE_H, t);// componente image
		bullet->addComponent<DisableOnExit>(DISABLEONEXIT_H);// conmponente de desactivar al desaparecer
		bullet->addComponent<BulletInfo>(BULLETINFO_H, id);// información de la bala
	}
}

void BulletNetSystem::DisableOnExitUpdate(Entity* a, Transform* tr_) {
	int x = tr_->pos_.getX();
	int y = tr_->pos_.getY();

	float wWidth_ = sdlutils().width();// ancho de ventana
	float wHeight_ = sdlutils().height();// alto de ventana

	// si se sale de los límites de la ventana elimina las balas
	if ((x < 0 - tr_->w_) || (x + tr_->w_ > wWidth_) || (y < 0 - tr_->h_) || (y + tr_->h_ > wHeight_)) {
		a->setAlive(false);
	}
}

void BulletNetSystem::shoot(const Message& m) {

	createBullet(m.shoot.pos.x, m.shoot.pos.y, m.shoot.vel.x, m.shoot.vel.y, m.shoot.id);

}

void BulletNetSystem::GameOver(const Message&) {
	running_ = false;
	for (Entity* b : mngr_->getEntitiesByGroup(_grp_BULLETS)) {
		b->setAlive(false);
	}
}

void BulletNetSystem::GameStart(const Message&) {
	running_ = true;
}
