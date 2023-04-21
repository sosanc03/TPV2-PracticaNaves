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

	createShip0();
	createShip1();
}

void FighterCtrlNetSystem::createShip0() {
	fighter0_ = mngr_->addEntity();
	Vector2D vel_ = Vector2D(0, 0);// velocidad incial
	int rot_ = 0;// rotación inicial
	
	Vector2D pos = Vector2D(0, sdlutils().height() / 2 - FIGHTER_SIZE / 2);
	uint32_t id = 0;
	fighter0_->addComponent<FighterInfo>(FIGHTERINFO_H, id);
	// transform del payer
	tr0_ = fighter0_->addComponent<Transform>(TRANSFORM_H, pos, vel_, FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	auto t = &sdlutils().images().at("fighter");
	fighter0_->addComponent<Image>(IMAGE_H, t);// componente imagen
	//fighter0_->addComponent<FighterCtrl>(FIGHTERCTRL_H);// componente fighter
	//fighter0_->addComponent<DeAcceleration>(DEACCELERATION_H);// componente de deaceleración
	//fighter0_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);// componente toroidal
}

void FighterCtrlNetSystem::createShip1() {
	fighter1_ = mngr_->addEntity();
	Vector2D vel_ = Vector2D(0, 0);// velocidad incial
	int rot_ = 0;// rotación inicial

	Vector2D pos = Vector2D(sdlutils().width() - FIGHTER_SIZE / 2, sdlutils().height() / 2 - FIGHTER_SIZE / 2);

	uint32_t id = 1;
	fighter1_->addComponent<FighterInfo>(FIGHTERINFO_H, id);
	// transform del payer
	tr1_ = fighter1_->addComponent<Transform>(TRANSFORM_H, pos, vel_, FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	auto t = &sdlutils().images().at("fighter");
	fighter1_->addComponent<Image>(IMAGE_H, t);// componente imagen
	//fighter1_->addComponent<FighterCtrl>(FIGHTERCTRL_H);// componente fighter
	//fighter1_->addComponent<DeAcceleration>(DEACCELERATION_H);// componente de deaceleración
	//fighter1_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);// componente toroidal
}

void FighterCtrlNetSystem::update() {
	if (!running_)
		return;
	auto netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);
	auto side = netSys->getSide();

	moveFighter(mngr_->getEntitiesByGroup(_grp_FIGHTERS).at(side));
	auto tr = mngr_->getEntitiesByGroup(_grp_FIGHTERS).at(side)->getComponent<Transform>(TRANSFORM_H);
	netSys->sendFighterPosition(tr);

}

void FighterCtrlNetSystem::handleGameStart(const Message&) {
	running_ = true;
}

void FighterCtrlNetSystem::handleGameOver(const Message& m) {
	auto netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);
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

void FighterCtrlNetSystem::showAtOppositeSide(Transform* tr)
{
	// show at opposite side
	if (tr->pos_.getX() < -tr->w_) {
		tr->pos_.setX(sdlutils().width());
	}
	else if (tr->pos_.getX() > sdlutils().width()) {
		tr->pos_.setX(-tr->w_);
	}

	if (tr->pos_.getY() < -tr->h_) {
		tr->pos_.setY(sdlutils().height());
	}
	else if (tr->pos_.getY() > sdlutils().height()) {
		tr->pos_.setY(-tr->h_);
	}
}

void FighterCtrlNetSystem::reduceVelocity(Transform* tr)
{
	// reduce velocity
	tr->speed_ = tr->speed_ * 0.995f;
	if (tr->speed_.magnitude() < 0.1f)
		tr->speed_ = Vector2D(0.0f, 0.0f);
}

void FighterCtrlNetSystem::moveFighter(Entity* fighter)
{
	auto& ihdlr = ih();

	auto tr = fighter->getComponent<Transform>(TRANSFORM_H);
	auto netSys = mngr_->getSystem<NetworkSystem>(_SYS_NETWORK);
	// handle input
	if (ihdlr.isKeyDown(SDL_SCANCODE_UP)) {
		auto thrust_ = 0.2f;
		if (tr->speed_.magnitude() < 5.0f)
			tr->speed_ = tr->speed_
			+ Vector2D(0, -1).rotate(tr->rot_) * thrust_;
	}
	else if (ihdlr.isKeyDown(SDL_SCANCODE_RIGHT)) {
		tr->rot_ += 2.0f;
	}

	if (ihdlr.isKeyDown(SDL_SCANCODE_DOWN)) {
		tr->speed_ = tr->speed_ * 0.75f;
	}
	else if (ihdlr.isKeyDown(SDL_SCANCODE_LEFT)) {
		tr->rot_ -= 2.0f;
	}

	//Shoot
	if (ihdlr.isKeyDown(SDL_SCANCODE_RETURN)) {
		auto fInfo = fighter->getComponent<FighterInfo>(FIGHTERINFO_H);
		if (fInfo->lastShoot_ + fInfo->shootRate_
			< sdlutils().currRealTime()) {
			auto bPos = tr->pos_
				+ Vector2D(tr->w_ / 2.0f, tr->h_ / 2.0f)
				- Vector2D(0.0f, tr->h_ / 2.0f + 5.0f).rotate(
					tr->rot_);
			auto bVel = Vector2D(0.0f, -1.0f).rotate(tr->rot_)
				* (tr->speed_.magnitude() + 5.0f);
			Message m;
			m.id = _MSG_SHOT;
			m.shoot.pos.x = bPos.getX();
			m.shoot.pos.y = bPos.getY();
			m.shoot.vel.x = bVel.getX();
			m.shoot.vel.y = bVel.getY();
			mngr_->send(m);
			fInfo->lastShoot_ = sdlutils().currRealTime();
			netSys->sendBulletShot(bPos.getX(), bPos.getY(), bVel.getX(), bVel.getY());
		}
	}

	// move
	tr->move();

	reduceVelocity(tr);

	showAtOppositeSide(tr);

}

void FighterCtrlNetSystem::changeFighterPos(Uint16 side, float x, float y, float rot)
{
	auto tr = mngr_->getEntitiesByGroup(_grp_FIGHTERS).at(side)->getComponent<Transform>(TRANSFORM_H);
	tr->pos_.set(x, y);
	tr->rot_ = rot;
}