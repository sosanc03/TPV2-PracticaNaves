#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

struct Health : public Component {
public:
	Health();// constructora
	int lifes = 3; int maxHP_ = 3;
	int tSize_ = 50;// tamaño
};
