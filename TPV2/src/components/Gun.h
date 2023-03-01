#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../ecs/Manager.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/VirtualTimer.h"
#include "Transform.h"
#include "DisableOnExit.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

using namespace ecs;

class Gun : public Component {
private:
	float delayTime_, lastTime_;
	Transform* tr_ = nullptr;
	Texture* t_ = nullptr;
	int w_, h_;
public:
	Gun(float delayTime = 250.0f);
	void initComponent();
	void update();
	void createBullet();
};