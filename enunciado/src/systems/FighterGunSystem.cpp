#include "FighterGunSystem.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"

void FighterGunSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_GAME_PAUSED:
		onRoundOver();
		break;
	case _m_GAME_RESUME:
		onRoundStart();
		break;
	case _m_GAME_START:
		onRoundStart();
		break;
	default:
		break;
	}
}

FighterGunSystem::FighterGunSystem() :
	active_(true) {
	bulletTime = 0.0f;
}


FighterGunSystem::~FighterGunSystem()
{
}

void FighterGunSystem::update()
{
	if (active_) {
		auto& ihldr = ih();
		if (ihldr.keyDownEvent()&& ihldr.isKeyDown(SDL_SCANCODE_S))shoot();
	}
}

void FighterGunSystem::shoot()
{
	float time = sdlutils().currRealTime() / 1000;
	if (time - bulletTime >= 0.25) {
		{ // create start
			bulletTime = sdlutils().currRealTime() / 1000;
			Message shoot;
			shoot.id = _m_GUN_SHOT;

			auto tr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_PLAYER));
			auto bPos = tr_->pos_ + Vector2D(tr_->width_ / 2.0f, tr_->height_ / 2.0f) - Vector2D(0.0f, tr_->height_ / 2.0f + 5.0f + 12.0f).rotate(tr_->rot_) - Vector2D(2.0f, 10.0f);
			auto bVel = Vector2D(0.0f, -1.0f).rotate(tr_->rot_) * (tr_->vel_.magnitude() + 5.0f);

			shoot.FighterCoords.height = 20.0f;
			shoot.FighterCoords.width = 5.0f;
			shoot.FighterCoords.posX = bPos.getX();
			shoot.FighterCoords.posY = bPos.getY();
			shoot.FighterCoords.vX = bVel.getX();
			shoot.FighterCoords.vY = bVel.getY();
			shoot.FighterCoords.rotation = tr_->rot_;
			mngr_->send(shoot);
		}
	}
}

void FighterGunSystem::onRoundOver()
{
	active_ = false;
}

void FighterGunSystem::onRoundStart()
{
	active_ = true;
}
