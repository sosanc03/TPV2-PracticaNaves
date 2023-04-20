#pragma once
#include "../ecs/Component.h"

struct ShowAtOppositeSide : public Component {
	ShowAtOppositeSide() {};
	float margin_ = 20;
};
