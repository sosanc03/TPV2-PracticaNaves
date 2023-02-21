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
	float delay;
	Transform* tr = nullptr;
	VirtualTimer* timer = nullptr;
public:
	Gun();
	void initComponent();

	void update();
};