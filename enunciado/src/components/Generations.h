
#pragma once
#include "../ecs/Component.h"

struct Generations : public ecs::Component {
public:
	__CMPID_DECL__(ecs::_GENERATIONS)

		Generations() {};
	virtual ~Generations() {};

	int g_ = 0;
};


