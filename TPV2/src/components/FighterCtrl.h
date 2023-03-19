#pragma once
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

using namespace ecs;

struct FighterCtrl : public Component {
public:
	FighterCtrl() {};// constructora
	float maxVel = 40.0f, rot = 5.0f, thrust = 0.2f;
};
