#pragma once
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

using namespace ecs;

class DeAcceleration : public Component{
private:
	Transform* tr_ = nullptr;// transform
	float deaF_, limit_;// variables
public:
	DeAcceleration();// constructora
	~DeAcceleration();// destructora
	void initComponent();// inicio de componente
	void update();// update
};