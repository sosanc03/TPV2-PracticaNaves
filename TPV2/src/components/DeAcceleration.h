#pragma once
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

using namespace ecs;

class DeAcceleration : public Component{
private:
	Transform* tr = nullptr;
	float deaFactor, limit;
public:
	DeAcceleration();
	~DeAcceleration();
	void initComponent();
	void update();
};