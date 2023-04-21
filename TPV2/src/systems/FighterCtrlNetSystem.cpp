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

	// transform del payer
	tr0_ = fighter0_->addComponent<Transform>(TRANSFORM_H, pos, vel_, FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	auto t = &sdlutils().images().at("fighter");
	fighter0_->addComponent<Image>(IMAGE_H, t);// componente imagen
	fighter0_->addComponent<FighterCtrl>(FIGHTERCTRL_H);// componente fighter
	fighter0_->addComponent<DeAcceleration>(DEACCELERATION_H);// componente de deaceleración
	fighter0_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);// componente toroidal
}

void FighterCtrlNetSystem::createShip1() {
	fighter1_ = mngr_->addEntity();
	Vector2D vel_ = Vector2D(0, 0);// velocidad incial
	int rot_ = 0;// rotación inicial

	Vector2D pos = Vector2D(sdlutils().width() - FIGHTER_SIZE / 2, sdlutils().height() / 2 - FIGHTER_SIZE / 2);

	// transform del payer
	tr1_ = fighter1_->addComponent<Transform>(TRANSFORM_H, pos, vel_, FIGHTER_SIZE, FIGHTER_SIZE, rot_);
	auto t = &sdlutils().images().at("fighter");
	fighter1_->addComponent<Image>(IMAGE_H, t);// componente imagen
	fighter1_->addComponent<FighterCtrl>(FIGHTERCTRL_H);// componente fighter
	fighter1_->addComponent<DeAcceleration>(DEACCELERATION_H);// componente de deaceleración
	fighter1_->addComponent<ShowAtOppositeSide>(OPPOSITESIDE_H);// componente toroidal
}
