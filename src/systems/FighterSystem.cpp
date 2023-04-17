#include "FighterSystem.h"

void FighterSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _MSG_START: // inicio partida
		initSystem();
		break;
	case _MSG_PAUSE: // pausa
		active_ = false;
		break;
	case _MSG_RESUME: // resume
		active_ = true;
		break;
	case _MSG_GAMEOVER: // volver de ronda perdida
		onRoundStart();
		break;
	case _MSG_COL_AST_PLAYER: // perder ronda
		onCollision_FighterAsteroid();
		break;
	default:
		break;
	}
}

void FighterSystem::initSystem() {
	active_ = true;
	createShip();
}

void FighterSystem::createShip() {
	fighter_ = mngr_->addEntity();// nave

	Vector2D vel_ = Vector2D(0, 0);// velocidad incial
	int rot_ = 0;// rotación inicial
	Vector2D plCentralPos_ = Vector2D(sdlutils().width() / 2 - FIGHTER_SIZE / 2,
		sdlutils().height() / 2 - FIGHTER_SIZE / 2);

	// transform del payer
	Transform* playerTr_ = fighter_->addComponent<Transform>(TRANSFORM_H, plCentralPos_, vel_, FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	auto t = &sdlutils().images().at("fighter");
	fighter_->addComponent<Image>(IMAGE_H, t);// componente imagen
	fighter_->addComponent<FighterCtrl>(FIGHTERCTRL_H);// componente fighter
	fighter_->addComponent<DeAcceleration>(DEACCELERATION_H);// componente de deaceleración
	fighter_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);// componente toroidal
	fighter_->addComponent<Health>(HEALTH_H);// componente de salud
}


void FighterSystem::update() {
	if (active_) {
		fighterCtrlUpdate();
		deAccelerationUpdate();
		showAtOppositeSideUpdate();
		Transform* tr_ = fighter_->getComponent<Transform>(TRANSFORM_H);
		tr_->move();
	}
}


void FighterSystem::fighterCtrlUpdate()
{
	Transform* tr_ = fighter_->getComponent<Transform>(TRANSFORM_H);
	FighterCtrl* fi_ = fighter_->getComponent<FighterCtrl>(FIGHTERCTRL_H);

	if (InputHandler::instance()->keyDownEvent()) {
		//Rotación
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT))tr_->rot_ -= fi_->rot;
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT))tr_->rot_ += fi_->rot;
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
			Message m;
			m.id = _MSG_SHOT;
			mngr_->send(m);
		}
		//Movimiento
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_UP)) {
			float angle = (tr_->rot_ * PI) / 180.0f;// ángulo en radianes
			tr_->dir_ = Vector2D(sin(angle), -cos(angle));

			tr_->speed_ = tr_->speed_ + (tr_->dir_ * fi_->thrust);
			sdlutils().soundEffects().at("thrust").play();
		}
	}
}

void FighterSystem::deAccelerationUpdate()
{
	Transform* tr_ = fighter_->getComponent<Transform>(TRANSFORM_H);
	DeAcceleration* de_ = fighter_->getComponent<DeAcceleration>(DEACCELERATION_H);

	if (tr_->speed_.magnitude() <= de_->limit_) tr_->speed_ = Vector2D(0, 0);// nave parada
	else tr_->speed_ = tr_->speed_ * de_->deaF_; // velocidad 
}

void FighterSystem::showAtOppositeSideUpdate()
{
	Transform* tr_ = fighter_->getComponent<Transform>(TRANSFORM_H);
	ShowAtOppositeSide* op_ = fighter_->getComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);

	float wWidth_ = sdlutils().width();// ancho de ventana
	float wHeight_ = sdlutils().height();// alto de ventana

	// X
	if (tr_->pos_.getX() > wWidth_ + op_->margin_) tr_->pos_ = Vector2D((0 - op_->margin_), tr_->pos_.getY());
	else if (tr_->pos_.getX() < 0 - op_->margin_) tr_->pos_ = Vector2D((wWidth_ + op_->margin_), tr_->pos_.getY());

	// Y
	if (tr_->pos_.getY() > wHeight_ + op_->margin_) tr_->pos_ = Vector2D(tr_->pos_.getX(), (0 - op_->margin_));
	else if (tr_->pos_.getY() < 0 - op_->margin_) tr_->pos_ = Vector2D(tr_->pos_.getX(), (wHeight_ + op_->margin_));
}

void FighterSystem::resetPlayer()
{
	Transform* tr_ = fighter_->getComponent<Transform>(TRANSFORM_H);

	tr_->pos_ = Vector2D(sdlutils().width() / 2 - FIGHTER_SIZE / 2, sdlutils().height() / 2 - FIGHTER_SIZE / 2);// coloca al player en el centro
	tr_->speed_ = Vector2D(0, 0);// velocidad a 0
	tr_->rot_ -= tr_->rot_;// rotación a 0
}

void FighterSystem::onCollision_FighterAsteroid() {
	sdlutils().soundEffects().at("explosion").play();// sonido de expresión
	resetPlayer();
}

void FighterSystem::onRoundOver() {
	active_ = false;
}

void FighterSystem::onRoundStart() {
	active_ = true;
	resetPlayer();
}