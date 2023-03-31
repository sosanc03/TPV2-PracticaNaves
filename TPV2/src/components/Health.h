#pragma once
#include "../ecs/Component.h"

struct Health : public ecs::Component {
public:
	Health() {}// constructora
	int lifes = 3; int maxHP_ = 3;
	int tSize_ = 50;// tamaño
};
