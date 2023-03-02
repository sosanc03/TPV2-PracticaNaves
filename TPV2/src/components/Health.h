#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Health : public Component {
private:
	Texture* t_ = nullptr;
	Vector2D renderPos = Vector2D(0, 0);
	int lifes_;
	int maxHP_;
	int tSize_;
public:
	Health(int vidas);
	int getLifes();
	void subLife();
	void resetLifes();
	void render();
};
