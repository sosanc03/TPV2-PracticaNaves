#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/VirtualTimer.h"
#include "../components/Transform.h"
#include "../sdlutils/InputHandler.h"

using namespace ecs;

class Gun : public Component {
private:
	float delayTime;
	Transform* tr = nullptr;
	VirtualTimer* timer = nullptr;
public:
	Gun(float DelayTime = 0.25f);
	void initComponent();

	void update();
};