#pragma once
#include "../ecs/Component.h"

struct ShowAtOppositeSide : public ecs::Component {
	ShowAtOppositeSide() {};
	float margin_ = 20;
};
