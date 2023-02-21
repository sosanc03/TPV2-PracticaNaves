#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

class ShowAtOppositeSide : public Component {
private: 
	Transform* tr = nullptr;
	float WIDTH;
	float HEIGHT;

public:
	ShowAtOppositeSide();
	void initComponent();

	void update();
};
