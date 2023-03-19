#include "FighterSystem.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/Health.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"


void FighterSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_COL_AST_PLAYER:
		onCollision_FighterAsteroid();
		break;
	case _m_GAME_START:
		onGameStart();
		break;
	case _m_GAME_PAUSED:
		onRoundOver();
		break;
	case _m_GAME_RESUME:
		onRoundStart();
		break;
	default:
		break;
	}
}

FighterSystem::FighterSystem() : player(nullptr), active_(false) {
}

FighterSystem::~FighterSystem()
{
}

void FighterSystem::initSystem()
{
	//Init of the player
	if (active_) {
		player = mngr_->addEntity();
		mngr_->setHandler(ecs::_hdlr_PLAYER, player);
		auto tr = mngr_->addComponent<Transform>(player);
		//Player position and speed
		auto s = 50.0f;
		auto x = (sdlutils().width() - s) / 2.0f;
		auto y = (sdlutils().height() - s) / 2.0f;
		tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
		mngr_->addComponent<Image>(player, &sdlutils().images().at("fighter"));
		mngr_->addComponent<FighterCtrl>(player);
		mngr_->addComponent<DeAcceleration>(player);
		mngr_->addComponent<Health>(player);
	}

}

void FighterSystem::update()
{
	if (active_) {
		FighterCtrlUpdate();
		DecelerateUpdate();
		ShowAtOppositeSideUpdate();
		auto* tr_ = mngr_->getComponent<Transform>(player);
		tr_->move();
	}
}

void FighterSystem::DecelerateUpdate()
{
	auto* tr = mngr_->getComponent<Transform>(player);
	auto dec = mngr_->getComponent<DeAcceleration>(player)->deceleration;
	auto& vel_ = tr->vel_;
	vel_.set(vel_ * dec);
	if (vel_.magnitude() < 0.05f) vel_.set(0.0f, 0.0f);
}

void FighterSystem::ShowAtOppositeSideUpdate()
{
	auto* tr_ = mngr_->getComponent<Transform>(player);

	// check left/right borders
	if (tr_->pos_.getX() + tr_->width_ < 0) {
		tr_->pos_.setX(sdlutils().width());
	}
	else if (tr_->pos_.getX() > sdlutils().width()) {

		tr_->pos_.setX(-tr_->width_);
	}

	// check upper/lower borders
	if (tr_->pos_.getY() + tr_->height_ < 0) {
		tr_->pos_.setY(sdlutils().height());
	}
	else if (tr_->pos_.getY() > sdlutils().height()) {
		tr_->pos_.setY(-tr_->height_);
	}
}

void FighterSystem::onRoundOver()
{
	active_ = false;
}

void FighterSystem::onRoundStart()
{
	active_ = true;
	resetPosition();
}

void FighterSystem::onGameStart()
{
	active_ = true;
	initSystem();
}

void FighterSystem::resetPosition()
{
	auto* tr_ = mngr_->getComponent<Transform>(player);
	tr_->pos_ = Vector2D(sdlutils().width() / 2 - tr_->width_ / 2, sdlutils().height() / 2 - tr_->height_ / 2);
	tr_->rot_ = 0.0;
	tr_->vel_ = Vector2D(0, 0);
}

void FighterSystem::onCollision_FighterAsteroid()
{
	resetPosition();
	mngr_->getComponent<Health>(player)->h_--;
}

void FighterSystem::FighterCtrlUpdate()
{
	auto& ihldr = ih();
	auto* tr_ = mngr_->getComponent < Transform >(player);

	auto th = mngr_->getComponent<FighterCtrl>(player)->thurst;
	auto sp = mngr_->getComponent<FighterCtrl>(player)->speedLimit;

	if (ihldr.keyDownEvent()) {

		auto& vel_ = tr_->vel_;
		auto rot = tr_->rot_;
		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			tr_->rot_ = rot + 5.0f;
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			tr_->rot_ = rot - 5.0f;
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) {

			sdlutils().soundEffects().at("thrust").play(0, 1);
			vel_ = vel_ + Vector2D(0, -1).rotate(rot) * th;
			if (vel_.magnitude() > sp)
				vel_=vel_.normalize()* sp;
		}

	}
}
