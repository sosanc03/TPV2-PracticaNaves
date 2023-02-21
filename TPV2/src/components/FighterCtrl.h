#pragma once
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

using namespace ecs;

class FighterCtrl : public Component {
private:
	Transform* tr = nullptr;
	float speed, maxSpeed, rotation;
public:
	FighterCtrl();
	FighterCtrl(float Velocity, float MaxVelocity, float Rotation);
	void initComponent();
	void handleEvents(SDL_Event event);
	void update();
};
