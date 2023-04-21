// This file is part of the course TPV2@UCM - Samir Genaim

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
		handleGameOver(m);
		break;
	case _MSG_START:
		handleGameStart(m);
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

		// move the bullet
		bTR->move();

		// disable if exit from window
		if ((bTR->pos_.getX() < -bTR->w_
			|| bTR->pos_.getX() > sdlutils().width())
			|| bTR->pos_.getY() < -bTR->h_
			|| bTR->pos_.getY() > sdlutils().height()) {
			b->setAlive(false);
		}
		netSys->sendBulletPosition(bTR);
	}
}

void BulletNetSystem::changeBulletPos(float x, float y, float rot)
{
}

void BulletNetSystem::createNewBullet(float posX, float posY, float velX, float velY)
{
	Entity* b = mngr_->addEntity(_grp_BULLETS);

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
	auto t = &sdlutils().images().at("bullet");
	b->addComponent<Image>(IMAGE_H, t);

	sdlutils().soundEffects().at("fire").play();
}

void BulletNetSystem::handleShoot(const Message& m) {

	createNewBullet(m.shoot.pos.x, m.shoot.pos.y, m.shoot.vel.x, m.shoot.vel.y);

}

void BulletNetSystem::handleGameOver(const Message&) {
	running_ = false;
	for (Entity* b : mngr_->getEntitiesByGroup(_grp_BULLETS)) {
		b->setAlive(false);
	}
}

void BulletNetSystem::handleGameStart(const Message&) {
	running_ = true;
}
