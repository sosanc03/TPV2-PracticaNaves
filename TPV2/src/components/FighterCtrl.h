#pragma once
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

using namespace ecs;

class FighterCtrl : public Component {
private:
	Transform* tr_ = nullptr;
	float maxVel_, rot_, thrust_;
public:
	FighterCtrl(float maxVel = 40.0f, float rot = 5.0f, float thrust = 0.2f);
	void initComponent();
	void update();
};
