#pragma once
#include "../ecs/Component.h"

struct DeAcceleration : public ecs::Component{
	DeAcceleration() {}// constructora
	float deaF_ = 0.995f;// factor de deceleraci�n
	float limit_ = 0.005;// m�nimo de velocidad antes de que la nave se pare
};