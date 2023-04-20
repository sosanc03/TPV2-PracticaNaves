#pragma once
#include "../ecs/Component.h"

using namespace ecs;

struct FighterCtrl : public Component {
	FighterCtrl() {};// constructora
	float maxVel = 40.0f, rot = 5.0f, thrust = 0.2f;
};
