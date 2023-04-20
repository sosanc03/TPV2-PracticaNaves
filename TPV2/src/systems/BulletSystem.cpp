#include "BulletSystem.h"
#include "FighterSystem.h"

void BulletSystem::receive(const ecs::Message& m) {
	switch (m.id)
	{
	case _MSG_SHOT: // disparo
		shoot(Vector2D(m.fighterStruct.posX, m.fighterStruct.posY), Vector2D(m.fighterStruct.velX,
			m.fighterStruct.velY),m.fighterStruct.width, m.fighterStruct.height, m.fighterStruct.rotation);
		break;
	case _MSG_COL_AST_BULLET: // bala con ast
		onCollision_BulletAsteroid(m.hitBulAst.bullet_);
		break;
	case _MSG_START: // principio partida
		initSystem();
		break;
	case _MSG_PAUSE: // pausa
		active_ = false;
		break;
	case _MSG_RESUME: // reanudacion
		onRoundStart();
		break;
	case _MSG_GAMEOVER: // volver de perder ronda
		onRoundStart();
		break;
	case _MSG_COL_AST_PLAYER: // perder ronda
		onRoundOver();
		break;
	default:
		break;
	}
}

void BulletSystem::initSystem() {
	fSys_ = mngr_->getSystem<FighterSystem>(_SYS_FIGHTER);
	active_ = true;
	cont_ = 0;
}

void BulletSystem::update() {
	if (active_) {
		for (auto a : mngr_->getEntitiesByGroup(_grp_BULLETS)) {
			Transform* tr_ = a->getComponent<Transform>(TRANSFORM_H);
			DisableOnExitUpdate(a);
			tr_->move();
		}
	}
}

void BulletSystem::shoot(Vector2D pos, Vector2D vel, float width, float height, float rotation) {
	if (sdlutils().currRealTime() >= cont_){
		cont_ = sdlutils().currRealTime() + 250; // 250ms

		sdlutils().soundEffects().at("fire").play(); // sonido disparo

		Entity* bullet = mngr_->addEntity(_grp_BULLETS);// bala

		int w_ = 10;// ancho
		int h_ = 25;// alto
		Transform* playerTr_ = fSys_->fighter_->getComponent<Transform>(TRANSFORM_H);
		int w = playerTr_->w_; int h = playerTr_->h_; float r = playerTr_->rot_;// ancho, alto y rotación

		Vector2D bPos = playerTr_->pos_
			+ Vector2D(w / 2.0f, h / 2.0f)
			- Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r)
			- Vector2D(2.0f, 10.0f);// posición
		Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(r) * (playerTr_->speed_.magnitude() + 5.0f);// velocidad
		auto t = &sdlutils().images().at("bullet");
		bullet->addComponent<Transform>(TRANSFORM_H, bPos, bVel, w_, h_, r);// transform
		bullet->addComponent<Image>(IMAGE_H, t);// componente image
		bullet->addComponent<DisableOnExit>(DISABLEONEXIT_H);// conmponente de desactivar al desaparecer
	}
}

void BulletSystem::onCollision_BulletAsteroid(Entity* b) {
	b->setAlive(false);
}

void BulletSystem::onRoundOver() {
	active_ = false;
	for (auto b : mngr_->getEntitiesByGroup(_grp_BULLETS)) {
		b->setAlive(false);
	}
}

void BulletSystem::onRoundStart() {
	active_ = true;
}

void BulletSystem::DisableOnExitUpdate(Entity* a) {

	Transform* tr_ = a->getComponent<Transform>(TRANSFORM_H);

	int x = tr_->pos_.getX();
	int y = tr_->pos_.getY();

	float wWidth_ = sdlutils().width();// ancho de ventana
	float wHeight_ = sdlutils().height();// alto de ventana

	// si se sale de los límites de la ventana elimina las balas
	if ((x < 0 - tr_->w_) || (x + tr_->w_ > wWidth_) || (y < 0 - tr_->h_) || (y + tr_->h_ > wHeight_)) {
		a->setAlive(false);
	}
}