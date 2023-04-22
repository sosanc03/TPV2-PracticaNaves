#include "BulletNetSystem.h"

BulletNetSystem::BulletNetSystem() :
	running_(false) {
}

BulletNetSystem::~BulletNetSystem() {
}

void BulletNetSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_SHOT:
		handleShoot(m);
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

void BulletNetSystem::createNewBullet(float posX, float posY, float velX, float velY, int id)
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

	/*Entity* b = mngr_->addEntity(_grp_BULLETS);

	// the bottom/center of the bullet
	Vector2D pos = Vector2D(posX, posY);

	// the velocity of the bullet
	Vector2D vel = Vector2D(velX, velY);

	// the image rotation
	float rot = Vector2D(0.0f, -1.0f).angle(vel);

	float bh = 18.0f;
	float bw = 6.f;

	// left/top corner of the bullet
	Vector2D bPos = pos + vel.normalize() * (bh / 2.0f)
		- Vector2D(bw / 2.0f, bh / 2.0);

	b->addComponent<Transform>(TRANSFORM_H, bPos, vel, bw, bh, rot);
	auto t = &sdlutils().images().at("bullet");// transform
	b->addComponent<Image>(IMAGE_H, t);// image
	b->addComponent<BulletInfo>(BULLETINFO_H, id);// información de la bala
	b->addComponent<DisableOnExit>(DISABLEONEXIT_H);// conmponente de desactivar al desaparecer

	sdlutils().soundEffects().at("fire").play();*/
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

void BulletNetSystem::handleShoot(const Message& m) {

	createNewBullet(m.shoot.pos.x, m.shoot.pos.y, m.shoot.vel.x, m.shoot.vel.y, m.shoot.id);

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
