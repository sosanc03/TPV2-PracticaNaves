// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>
#include <array>
#include <string>
#include "../ecs/System.h"

namespace ecs {
class Entity;
}

struct Transform;

class FightersSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_FIGHTERS)

	FightersSystem();
	virtual ~FightersSystem();

	void recieve(const Message&) override;
	void initSystem() override;
	void update() override;
	void changeFighterPos(Uint16 side, float x, float y, float rot);
private:
	void handleGameStart(const Message&);
	void handleGameOver(const Message&);
	void handleBulletHitFighter(const Message&);
	void showAtOppositeSide(Transform* tr);
	void reduceVelocity(Transform* tr);
	void moveFighter(ecs::Entity* fighter);

	Transform *tr0_;
	Transform *tr1_;
	std::string myName;
	std::string enemyName;
	bool running_;
};

