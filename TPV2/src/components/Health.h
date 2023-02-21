#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

class Health : public Component {
private:
	Texture* te = nullptr;
	int lifes;
	int maxLife;
public:
	Health(int vidas);
	int getLifes();
	void subLife();
	void resetLifes();
};
