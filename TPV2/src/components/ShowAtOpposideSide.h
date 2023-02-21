#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

const float WIDTH = SDLUtils::instance()->width();
const float HEIGHT = SDLUtils::instance()->height();
class ShowAtOppositeSide : public Component {
private: 
	Transform* tr = nullptr;

public:
	void initComponent();

	void update();
};
