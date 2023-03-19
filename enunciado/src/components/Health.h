#pragma once

#include "../ecs/Component.h"

struct Health : public ecs::Component {
public:
	__CMPID_DECL__(ecs::_HEALTH)

		Health() {};
	virtual ~Health() {};

	int h_ = 3.0;
};

