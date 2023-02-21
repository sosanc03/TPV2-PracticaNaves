#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

class Health : public Component {
private:
	Texture* te = nullptr;
	int life, maxLife;
public:
	Health(int vidas);
	int getLifes();
	void lessLife();
	void resetLifes();
};
