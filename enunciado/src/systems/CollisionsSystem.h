// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/System.h"
#include "../CheckML.h"
struct Transform;

class CollisionsSystem: public ecs::System {
public:

	__SYSID_DECL__(ecs::_sys_COLLISIONS)

	void recieve(const Message&) override;
	CollisionsSystem();
	virtual ~CollisionsSystem();
	void initSystem() override;
	void update() override;
private:
	bool active_;
};

