#pragma once

#include "../ecs/Component.h"

struct DisableOnExit : public ecs::Component {
public:
	__CMPID_DECL__(ecs::_DISABLEONEXIT)
		DisableOnExit() {};
	virtual ~DisableOnExit() {};

	float deceleration = 0.995f;
};

