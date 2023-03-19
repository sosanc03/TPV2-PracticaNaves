#pragma once
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "Transform.h"

using namespace ecs;

struct DeAcceleration : public Component{
public:
	DeAcceleration() {}// constructora
	float deaF_ = 0.995f;// factor de deceleración
	float limit_ = 0.005;// mínimo de velocidad antes de que la nave se pare
};