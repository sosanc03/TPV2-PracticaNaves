#include "FighterCtrlNetSystem.h"


FighterCtrlNetSystem::FighterCtrlNetSystem() :
	tr0_(nullptr), tr1_(nullptr), running_(false) {
}

void FighterCtrlNetSystem::receive(const Message& m) {
	switch (m.id) {
	case _MSG_START:
		handleGameStart(m);
		break;
	case _MSG_GAMEOVER:
		handleGameOver(m);
		break;
	case _MSG_COL_BULLET_PLAYER:
		handleBulletHitFighter(m);
		break;
	default:
		break;
	}
}

void FighterCtrlNetSystem::initSystem() {
	netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);
	createShip0();
	createShip1();
}

void FighterCtrlNetSystem::createShip0() {
	fighter0_ = mngr_->addEntity(_grp_FIGHTERS);
	Vector2D vel_ = Vector2D(0, 0);// velocidad incial
	int rot_ = 0;// rotación inicial
	
	Vector2D pos = Vector2D(0, sdlutils().height() / 2 - FIGHTER_SIZE / 2);
	uint32_t id = 0;
	fighter0_->addComponent<FighterInfo>(FIGHTERINFO_H, id);
	// transform del payer
	tr0_ = fighter0_->addComponent<Transform>(TRANSFORM_H, pos, vel_, FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	auto t = &sdlutils().images().at("fighter");
	fighter0_->addComponent<Image>(IMAGE_H, t);// componente imagen
	fighter0_->addComponent<FighterCtrl>(FIGHTERCTRL_H);// componente fighter
	fighter0_->addComponent<DeAcceleration>(DEACCELERATION_H);// componente de deaceleración
	fighter0_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);// componente toroidal
}

void FighterCtrlNetSystem::createShip1() {
	fighter1_ = mngr_->addEntity(_grp_FIGHTERS);
	Vector2D vel_ = Vector2D(0, 0);// velocidad incial
	int rot_ = 0;// rotación inicial

	Vector2D pos = Vector2D(sdlutils().width() - FIGHTER_SIZE, sdlutils().height() / 2 - FIGHTER_SIZE / 2);

	uint32_t id = 1;
	fighter1_->addComponent<FighterInfo>(FIGHTERINFO_H, id);
	// transform del payer
	tr1_ = fighter1_->addComponent<Transform>(TRANSFORM_H, pos, vel_, FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	auto t = &sdlutils().images().at("fighter2");
	fighter1_->addComponent<Image>(IMAGE_H, t);// componente imagen
	fighter1_->addComponent<FighterCtrl>(FIGHTERCTRL_H);// componente fighter
	fighter1_->addComponent<DeAcceleration>(DEACCELERATION_H);// componente de deaceleración
	fighter1_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);// componente toroidal
}

void FighterCtrlNetSystem::update() {
	if (!running_)
		return;
	auto netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);
	auto side = netSys->getSide();

	//moveFighter(mngr_->getEntitiesByGroup(_grp_FIGHTERS).at(side));
	Entity* p = mngr_->getEntitiesByGroup(_grp_FIGHTERS).at(side);
	Transform* tr = p->getComponent<Transform>(TRANSFORM_H);
	FighterCtrl* fi = p->getComponent<FighterCtrl>(FIGHTERCTRL_H);
	DeAcceleration* de = p->getComponent<DeAcceleration>(DEACCELERATION_H);
	ShowAtOppositeSide* op = p->getComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);

	fighterCtrlUpdate(tr, fi);
	deAccelerationUpdate(tr, de);
	showAtOppositeSideUpdate(tr, op);

	// move
	tr->move();
	
	netSys->sendFighterPosition(tr);

}

void FighterCtrlNetSystem::handleGameStart(const Message&) {
	running_ = true;
}

void FighterCtrlNetSystem::handleGameOver(const Message& m) {
	running_ = false;
	tr0_->pos_ = Vector2D(10.0f, (sdlutils().height() - tr0_->h_) / 2.0f);
	tr0_->speed_ = Vector2D();
	tr0_->rot_ = 90.0f;

	tr1_->pos_ = Vector2D(sdlutils().width() - tr1_->w_ - 10.0f,
		(sdlutils().height() - tr1_->h_) / 2.0f);
	tr1_->speed_ = Vector2D();
	tr1_->rot_ = -90.0f;

	auto sendTr = mngr_->getEntitiesByGroup(_grp_FIGHTERS).at(netSys->getSide())->getComponent<Transform>(TRANSFORM_H);
	netSys->sendFighterPosition(sendTr);
}

void FighterCtrlNetSystem::handleBulletHitFighter(const Message&) {
	sdlutils().soundEffects().at("explosion").play();
}

void FighterCtrlNetSystem::fighterCtrlUpdate(Transform* tr_, FighterCtrl* fi_) {
	if (InputHandler::instance()->keyDownEvent()) {
		//Rotación
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT))tr_->rot_ -= fi_->rot;
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT))tr_->rot_ += fi_->rot;
		if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_S)) {
			int w = tr_->w_; int h = tr_->h_; float r = tr_->rot_;// ancho, alto y rotación

			Vector2D bPos = tr_->pos_
				+ Vector2D(w / 2.0f, h / 2.0f)
				- Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r)
				- Vector2D(2.0f, 10.0f);// posición
			Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(r) * (tr_->speed_.magnitude() + 5.0f);// velocidad
			
			
			Message m;
			m.id = _MSG_SHOT;
			m.shoot.pos.x = bPos.getX();
			m.shoot.pos.y = bPos.getY();
			m.shoot.vel.x = bVel.getX();
			m.shoot.vel.y = bVel.getY();
			m.shoot.id = netSys->getSide();
			mngr_->send(m);

			netSys->sendBulletShot(bPos.getX(), bPos.getY(), bVel.getX(), bVel.getY(), r);
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

void FighterCtrlNetSystem::deAccelerationUpdate(Transform* tr_, DeAcceleration* de_) {
	if (tr_->speed_.magnitude() <= de_->limit_) tr_->speed_ = Vector2D(0, 0);// nave parada
	else tr_->speed_ = tr_->speed_ * de_->deaF_; // velocidad 
}

void FighterCtrlNetSystem::showAtOppositeSideUpdate(Transform* tr_, ShowAtOppositeSide* op_) {
	float wWidth_ = sdlutils().width();// ancho de ventana
	float wHeight_ = sdlutils().height();// alto de ventana

	// X
	if (tr_->pos_.getX() > wWidth_ + op_->margin_) tr_->pos_ = Vector2D((0 - op_->margin_), tr_->pos_.getY());
	else if (tr_->pos_.getX() < 0 - op_->margin_) tr_->pos_ = Vector2D((wWidth_ + op_->margin_), tr_->pos_.getY());

	// Y
	if (tr_->pos_.getY() > wHeight_ + op_->margin_) tr_->pos_ = Vector2D(tr_->pos_.getX(), (0 - op_->margin_));
	else if (tr_->pos_.getY() < 0 - op_->margin_) tr_->pos_ = Vector2D(tr_->pos_.getX(), (wHeight_ + op_->margin_));
}


void FighterCtrlNetSystem::changeFighterPos(Uint16 side, float x, float y, float rot)
{
	auto tr = mngr_->getEntitiesByGroup(_grp_FIGHTERS).at(side)->getComponent<Transform>(TRANSFORM_H);
	tr->pos_.set(x, y);
	tr->rot_ = rot;
}

