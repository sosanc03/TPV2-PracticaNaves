#include "FighterSystem.h"

void FighterSystem::receive(const Message& m) {
	switch (m.id)
	{
	case _MSG_START:
		initSystem();
		break;
	case _MSG_PAUSE:
		onRoundOver();
		break;
	case _MSG_RESUME:
		onRoundStart();
		break;
	case _MSG_COL_AST_PLAYER:
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
	mngr_->setHandler(ecs::_HDLR_PLAYER, fighter_);

	Vector2D vel_ = Vector2D(0, 0);// velocidad incial
	int rot_ = 0;// rotación inicial
	Vector2D plCentralPos_ = Vector2D(sdlutils().width() / 2 - FIGHTER_SIZE / 2, sdlutils().height() / 2 - FIGHTER_SIZE / 2);

	// transform del payer
	Transform* playerTr_ = mngr_->addComponent<Transform>(fighter_, plCentralPos_, vel_, FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	mngr_->addComponent<Image>(fighter_, &sdlutils().images().at("fighter"));// componente imagen
	mngr_->addComponent<FighterCtrl>(fighter_);// componente fighter
	mngr_->addComponent<DeAcceleration>(fighter_);// componente de deaceleración
	mngr_->addComponent<ShowAtOppositeSide>(fighter_);// componente toroidal

	int lifes = 3;// número de vidas
	mngr_->addComponent<Health>(fighter_, lifes);// componente de salud
}


void FighterSystem::update() {
	if (active_) {
		fighterCtrlUpdate();
		deAccelerationUpdate();
		showAtOppositeSideUpdate();
		Transform* tr_ = mngr_->getComponent<Transform>(fighter_);
		tr_->move();
	}
}


void FighterSystem::fighterCtrlUpdate()
{
	Transform* tr_ = mngr_->getComponent<Transform>(fighter_);
	FighterCtrl* fi_ = mngr_->getComponent<FighterCtrl>(fighter_);

	if (InputHandler::instance()->keyDownEvent()) {
		//Rotación
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT))tr_->rot_ = -fi_->rot;
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT))tr_->rot_ = fi_->rot;

		//Movimiento
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_UP)) {
			// modificar dir
			float angle = (tr_->rot_ * PI) / 180.0f;// ángulo en radianes
			tr_->dir_ = Vector2D(sin(angle), -cos(angle));

			tr_->speed_ = tr_->speed_ + (tr_->dir_ * fi_->thrust);
			sdlutils().soundEffects().at("thrust").play();
		}
	}
}

void FighterSystem::deAccelerationUpdate()
{
	Transform* tr_ = mngr_->getComponent<Transform>(fighter_);
	DeAcceleration* de_ = mngr_->getComponent<DeAcceleration>(fighter_);

	if (tr_->speed_.magnitude() <= de_->limit_) tr_->speed_ = Vector2D(0, 0);// nave parada
	else tr_->speed_ = tr_->speed_ * de_->deaF_; // velocidad 
}

void FighterSystem::showAtOppositeSideUpdate()
{
	Transform* tr_ = mngr_->getComponent<Transform>(fighter_);
	ShowAtOppositeSide* op_ = mngr_->getComponent<ShowAtOppositeSide>(fighter_);

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
	Transform* tr_ = mngr_->getComponent<Transform>(fighter_);

	tr_->pos_ = Vector2D(sdlutils().width() / 2 - FIGHTER_SIZE / 2, sdlutils().height() / 2 - FIGHTER_SIZE / 2);// coloca al player en el centro
	tr_->speed_ = Vector2D(0, 0);// velocidad a 0
	tr_->rot_ = -tr_->rot_;// rotación a 0
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