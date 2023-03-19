// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include "../CheckML.h"

class RenderSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_RENDER)

	RenderSystem();
	virtual ~RenderSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& m);

private:
	void drawMsgs();
	void drawFighter();
	void drawHealth();
	void drawAsteroids();
	void drawBullet();
	float initime = 0.0;
	bool win = false;
};

