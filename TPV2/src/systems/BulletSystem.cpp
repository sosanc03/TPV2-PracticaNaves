#include "BulletSystem.h"

void BulletSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _MSG_SHOT:
		shoot(Vector2D(m.fighterStruct.posX, m.fighterStruct.posY), Vector2D(m.fighterStruct.velX, m.fighterStruct.velY),
			m.fighterStruct.width, m.fighterStruct.height, m.fighterStruct.rotation);
		break;
	case _MSG_COL_AST_BULLET:
		onCollision_BulletAsteroid(m.hitBulAst.bullet_);
		break;
	case _MSG_START:
		initSystem();
		break;
	case _MSG_PAUSE:
		onRoundOver();
		break;
	case _MSG_RESUME:
		onRoundStart();
		break;
	default:
		break;
	}
}

void BulletSystem::initSystem() {
	active_ = true;
}

void BulletSystem::update() {
	if (active_) {

		for (auto a : mngr_->getEntities(ecs::_grp_BULLETS)) {
			Transform* tr_ = mngr_->getComponent<Transform>(a);
			DisableOnExitUpdate(a);
			tr_->move();
		}
	}
}

void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, float rotation) {
	ecs::Entity* bullet = mngr_->addEntity(ecs::_grp_BULLETS);// bala

	int w_ = 10;// ancho
	int h_ = 25;// alto
	Transform* playerTr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_HDLR_PLAYER));
	int w = playerTr_->w_; int h = playerTr_->h_; float r = playerTr_->rot_;// ancho, alto y rotación
	
	Vector2D bPos = playerTr_->pos_
		+ Vector2D(w / 2.0f, h / 2.0f)
		- Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r)
		- Vector2D(2.0f, 10.0f);// posición
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(r) * (playerTr_->speed_.magnitude() + 5.0f);// velocidad

	mngr_->addComponent<Transform>(bullet, bPos, bVel, w_, h_, r);// transform
	mngr_->addComponent<Image>(bullet, &(SDLUtils::instance()->images().at("bullet")));// componente image
	mngr_->addComponent<DisableOnExit>(bullet);// conmponente de desactivar al desaparecer

}

void BulletSystem::onCollision_BulletAsteroid(ecs::Entity* b) {
	mngr_->setAlive(b, false);
}

void BulletSystem::onRoundOver() {
	active_ = false;
	for (auto b : mngr_->getEntities(ecs::_grp_BULLETS)) {
		mngr_->setAlive(b, false);
	}
}

void BulletSystem::onRoundStart() {

}

void BulletSystem::DisableOnExitUpdate(ecs::Entity* a) {

	Transform* tr_ = mngr_->getComponent<Transform>(a);

	int x = tr_->pos_.getX();
	int y = tr_->pos_.getY();

	float wWidth_ = sdlutils().width();// ancho de ventana
	float wHeight_ = sdlutils().height();// alto de ventana

	// si se sale de los límites de la ventana elimina las balas
	if ((x < 0 - tr_->w_) || (x + tr_->w_ > wWidth_) || (y < 0 - tr_->h_) || (y + tr_->h_ > wHeight_)) {
		mngr_->setAlive(a, false);
	}
}