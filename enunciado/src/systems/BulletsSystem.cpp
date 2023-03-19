#include "BulletsSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Image.h"
#include "../components/DisableOnExit.h"
#include "../components/Transform.h"

void BulletsSystem::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_GUN_SHOT:
		shoot(Vector2D(m.FighterCoords.posX, m.FighterCoords.posY), Vector2D(m.FighterCoords.vX, m.FighterCoords.vY),
			m.FighterCoords.width, m.FighterCoords.height, m.FighterCoords.rotation);
		break;
	case _m_COL_BULLET_AST:
		onCollision_BulletAsteroid(m.bullet_hit_asteroid.bull);
		break;
	case _m_GAME_PAUSED:
		onRoundOver();
		break;
	case _m_GAME_START:
		active_ = true;
		break;
	case _m_GAME_RESUME:
		onRoundStart();
		break;
	default:
		break;
	}
}

BulletsSystem::BulletsSystem() :active_(true) {
}

BulletsSystem::~BulletsSystem()
{
}

void BulletsSystem::update()
{
	if (active_) {

		for (auto a : mngr_->getEntities(ecs::_grp_BULLETS)) {
			auto* tr_ = mngr_->getComponent<Transform>(a);
			DisableOnExitUpdate(a);
			tr_->move();
		}
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, double rot)
{
	sdlutils().soundEffects().at("fire").play(0, 2);
	auto bullet = mngr_->addEntity(ecs::_grp_BULLETS);
	auto tr_ = mngr_->addComponent<Transform>(bullet);

	tr_->init(pos, vel, width, height, rot);
	mngr_->addComponent<Image>(bullet, &sdlutils().images().at("fire"));
	mngr_->addComponent<DisableOnExit>(bullet);
	bulletTime = sdlutils().currRealTime() / 1000;
}

void BulletsSystem::DisableOnExitUpdate(ecs::Entity* bullet)
{
	auto* tr_ = mngr_->getComponent<Transform>(bullet);
	auto& pos = tr_->pos_;
	if (pos.getX() > sdlutils().width() + tr_->width_ / 2 || pos.getX() - tr_->width_ / 2 < 0)  mngr_->setAlive(bullet, false);
	else if (pos.getY() > sdlutils().height()- tr_->height_ / 2 || pos.getY() + tr_->height_ / 2 < 0)  mngr_->setAlive(bullet, false);
}

void BulletsSystem::onCollision_BulletAsteroid(ecs::Entity* b)
{
	mngr_->setAlive(b, false);
}

void BulletsSystem::onRoundOver()
{
	active_ = false;
	for (auto a : mngr_->getEntities(ecs::_grp_BULLETS)) {
		mngr_->setAlive(a, false);
	}
}

void BulletsSystem::onRoundStart()
{
	active_ = true;
}
