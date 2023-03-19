#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

struct ShowAtOppositeSide : public Component {
public:
	ShowAtOppositeSide() {};
	float margin_ = 20;
};
