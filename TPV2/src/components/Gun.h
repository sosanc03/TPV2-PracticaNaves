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

struct Gun : public Component {
private:
	
public:
	Gun() {};// contructora
	float delayTime_ = 250.0f, lastTime_ = 0.0f;// variables
	int w_ = 10, h_ = 25;// anchura y altura
};