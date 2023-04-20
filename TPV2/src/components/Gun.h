#pragma once
#include "../ecs/Component.h"

struct Gun : public Component {
	Gun() {};// contructora
	float delayTime_ = 250.0f, lastTime_ = 0.0f;// variables
	int w_ = 10, h_ = 25;// anchura y altura
};