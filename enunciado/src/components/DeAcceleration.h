// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"

struct DeAcceleration : public ecs::Component {
public:
	__CMPID_DECL__(ecs::_DEACCELERATION)
		DeAcceleration() {};
	virtual ~DeAcceleration() {};

	float deceleration = 0.995f;
};

