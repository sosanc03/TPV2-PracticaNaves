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
	float delayTime_, lastTime_;// variables
	Transform* tr_ = nullptr;// transoform
	Texture* t_ = nullptr;// textura
	int w_, h_;// anchura y altura
public:
	Gun(float delayTime = 250.0f);// contructora
	void initComponent();// init
	void update();// update
	void createBullet();// crea bala
};