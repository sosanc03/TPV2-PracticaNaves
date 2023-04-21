// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"

class BulletsSystem: public ecs::System {
public:
	__SYSID_DECL__(ecs::_sys_BULLETS)

	BulletsSystem();
	virtual ~BulletsSystem();

	void recieve(const Message&) override;
	void initSystem() override;
	void update() override;

	void changeBulletPos(float x, float y, float rot);
	void createNewBullet(float posX, float posY, float velX, float velY);
private:
	void handleShoot(const Message&);
	void handleGameOver(const Message&);
	void handleGameStart(const Message&);

	bool running_;
};

