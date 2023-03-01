#pragma once

#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

const float WIDTH = SDLUtils::instance()->width();
const float HEIGHT = SDLUtils::instance()->height();
class ShowAtOppositeSide : public Component {
private: 
	Transform* tr_ = nullptr;
	float wWidth_;
	float wHeight_;
	float w_;
	float h_;
	float margin_;

public:
	void initComponent();

	void update();
};
